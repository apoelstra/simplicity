{-# LANGUAGE ScopedTypeVariables, RecordWildCards #-}
-- | The module builds a Simplicity expression that mimics the behavour of a @CHECKSIG@ operation restricted to a @SIGHASH_ALL@ flag, for Bitcoin.
-- This forms the mimial Simiplicity expression needed to secure funds in a Bitcoin-style blockchain.
-- This uses Schnorr signature verification specified in "Simplicity.Programs.LibSecp256k1".
module Simplicity.Bitcoin.Programs.CheckSigHashAll
  ( Lib(Lib), mkLib
  -- * Operations
  , sigAllCMR
  , sigHashAll
  , checkSigHashAll
  , wCheckSigHashAll
  , pkwCheckSigHashAll
  -- * Types
  , Hash, PubKey, Sig
  -- * Example instances
  , lib
  ) where

import Simplicity.Bitcoin.Primitive
import Simplicity.Bitcoin.Term
import Simplicity.Digest
import Simplicity.Functor
import Simplicity.MerkleRoot
import qualified Simplicity.LibSecp256k1.Schnorr as Schnorr
import Simplicity.Programs.Bit
import Simplicity.Programs.Generic
import Simplicity.Programs.Sha256 hiding (Lib(Lib), lib)
import qualified Simplicity.Programs.Sha256 as Sha256
import qualified Simplicity.Programs.LibSecp256k1 as LibSecp256k1
import Simplicity.Programs.LibSecp256k1 (PubKey, Sig)
import Simplicity.Programs.Word
import Simplicity.Tensor
import Simplicity.Ty

-- | A collection of core Simplicity expressions for an Bitcoin-style sigHash.
-- Use 'mkLib' to construct an instance of this library.
data Lib term =
 Lib
  { -- | The commitment Merkle Root of the @sigAll@ expression that generates the data hashed for 'sigHashAll'.
    sigAllCMR :: Hash256

    -- | This expression returns a hash of basic signed transaction data.
    -- This includes:
    --
    -- * Hash of all the transaction inputs data.
    --
    -- * Hash of all the transaction output data.
    --
    -- * The transactions lock time.
    --
    -- * The transactions version data.
    --
    -- * The index of the input currently being spend.
    --
    -- * The asset and amount of this input's UTXO being redeemed.
  , sigHashAll :: term () Hash
    -- | Given a public key and a schnorr signature, this expression asserts that the signature is valid for the public key and the message generated by 'sigHashAll'.
  , checkSigHashAll :: term (PubKey, Sig) ()
  }

instance SimplicityFunctor Lib where
  sfmap m Lib{..} =
   Lib
    { sigAllCMR = sigAllCMR
    , sigHashAll = m sigHashAll
    , checkSigHashAll = m checkSigHashAll
    }

-- | Build the Bitcoin sigHash 'Lib' library from its dependencies.
mkLib :: forall term. (Assert term, Primitive term) => Sha256.Lib (Product CommitmentRoot term) -- ^ "Simplicity.Programs.Sha256"
                                                    -> LibSecp256k1.Lib term -- ^ "Simplicity.Programs.LibSecp256k1"
                                                    -> Lib term
mkLib Sha256.Lib{..} libSecp256k1 = lib
 where
  sigAll :: (Product CommitmentRoot term) () (Block, Block)
  sigAll = blk1 &&& blk2
   where
    blk1 = primitive InputsHash &&& primitive OutputsHash
    blk2 = ((primitive CurrentValue &&& (primitive CurrentIndex &&& primitive LockTime)) &&& ((primitive Version &&& scribe (toWord32 0x80000000)) &&& zero word64)) &&& scribe (toWord256 (512+2*256+64+3*32))
  lib@Lib{..} =
   Lib
    { sigAllCMR = commitmentRoot (fstProduct sigAll)
    , sigHashAll =
       let
        iv = toWord256 . integerHash256 . ivHash $ signatureIv sigAllCMR
        hb = sndProduct hashBlock
       in
        sndProduct sigAll >>> (scribe iv &&& oh >>> hb) &&& ih >>> hb
    , checkSigHashAll = (oh &&& (unit >>> sigHashAll)) &&& ih >>> LibSecp256k1.schnorrAssert libSecp256k1
    }

-- | Given a public key this expression asserts that the given witness is a signature that is valid for the public key and the message generated by 'sigHashAll'.
wCheckSigHashAll :: (Assert term, Primitive term, Witness term) => Lib term -> Schnorr.Sig -> term PubKey ()
wCheckSigHashAll Lib{..} ~(Schnorr.Sig r s) = iden &&& (witness (toWord256 . toInteger $ r, toWord256 . toInteger $ s))
                                         >>> checkSigHashAll

-- | Given a static public key this expression asserts that the given witness is a signature that is valid for the public key and the message generated by 'sigHashAll'.
pkwCheckSigHashAll :: (Assert term, Primitive term, Witness term, TyC a) => Lib term -> Schnorr.PubKey -> Schnorr.Sig -> term a ()
pkwCheckSigHashAll Lib{..} (Schnorr.PubKey y x) ~(Schnorr.Sig r s) =
   scribe (toBit y, toWord256 . toInteger $ x) &&& (witness (toWord256 . toInteger $ r, toWord256 . toInteger $ s))
   >>> checkSigHashAll

-- | An instance of the Elements checkSigHash 'Lib' library.
-- This instance does not share its dependencies.
-- Users should prefer to use 'mkLib' in order to share library dependencies.
-- This instance is provided mostly for testing purposes.
lib :: (Assert term, Primitive term) => Lib term
lib = mkLib libSha256P libSecp256k1
 where
  libSha256P = Sha256.lib
  libSha256 = sndProduct `sfmap` libSha256P
  libSecp256k1 = LibSecp256k1.mkLib libSha256
