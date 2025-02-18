{-# LANGUAGE UndecidableInstances, RankNTypes #-}
-- | This module extends "Simplicity.Term.Core" to the full Simplicity languages by defining the remaining language extensions: 'Primitive' and 'Jet'.
-- The 'Simplicity' class combines all the features of the full Simplicity language under one constraint.
--
-- This is a separate module from "Simplicity.Term.Core" so that the core language need not depend on the "Simplicity.Primitive" module.
module Simplicity.Term
 ( module Simplicity.Term.Core
 , Primitive(..)
 , Jet(..)
 , Simplicity(..)
 ) where

import Control.Arrow (Kleisli(..))
import Control.Monad.Reader.Class (MonadReader(..))
import qualified Control.Monad.Fail as Fail

import Simplicity.Digest
import Simplicity.MerkleRoot.Impl
import Simplicity.Primitive
import Simplicity.Term.Core
import Simplicity.Tensor
import Simplicity.Ty

-- | This class embeds Blockchain 'Prim'itives into the Simplicity language.
-- The semantics for these primitives is mediated by the 'Simplicity.Primitive' module.
class Primitive term where
  primitive :: (TyC a, TyC b) => Prim a b -> term a b

-- | The Monad 'm' should be a commutative monad.
instance (MonadReader PrimEnv m, Fail.MonadFail m) => Primitive (Kleisli m) where
  primitive p = Kleisli $ \a -> do
   env <- ask
   let err = Fail.fail $ "Simplicity.Term.primitive in Primitive (Kleisli m) instance: " ++ primName p ++ " failed."
   maybe err return $ primSem p a env

-- | This class creates expressions for discounted jets.
-- Jets expressions exclude witness-like expressions such as 'Witness' and 'Delegate' and other discounted 'Jet' expressions.
class (Assert term, Primitive term) => Jet term where
  -- TODO: add discount parameter
  jet :: (TyC a, TyC b) => (forall term0. (Assert term0, Primitive term0) => term0 a b) -> term a b

-- | The Monad 'm' should be a commutative monad.
instance (MonadReader PrimEnv m, Fail.MonadFail m) => Jet (Kleisli m) where
  jet t = t

-- | The class for the full Simplicity language with delegation.
-- This includes 'Core', 'Assert', 'Primitive', 'Jet', 'Witness' and 'Delegate'.
class (Jet term, Witness term, Delegate term) => Simplicity term where

instance (Primitive p, Primitive q) => Primitive (Product p q) where
  primitive p = Product (primitive p) (primitive p)

instance (Jet p, Jet q) => Jet (Product p q) where
  jet t = Product (jet t) (jet t)

instance (Simplicity p, Simplicity q) => Simplicity (Product p q) where

instance Primitive Unit where
  primitive _ = Unit

instance Jet Unit where
  jet _ = Unit

instance Simplicity Unit where

instance Primitive CommitmentRoot where
  primitive = primitiveCommitmentImpl primPrefix primName

-- Jets commit to their types, so we use WitnessRoot here.
instance Jet CommitmentRoot where
  jet t = jetCommitmentImpl (witnessRoot t)

instance Simplicity CommitmentRoot where

instance Primitive WitnessRoot where
  primitive = primitiveWitnessImpl primPrefix primName

instance Jet WitnessRoot where
  jet t = jetWitnessImpl (witnessRoot t)
  -- Idea for alternative WitnessRoot instance:
  --     jet t = t
  -- Trasparent jet witnesses would mean we could define the jet class as
  --     jet :: (TyC a, TyC b) => (forall term0. (Assert term0, Primitive term0, Jet term0) => term0 a b) -> term a b
  -- And then jets could contain jets such that their Sementics, WitnessRoots, and hence CommitmentRoots would all be transparent to jet sub-experssions.
  -- Need to think carefully what this would mean for concensus, but I think it is okay.

instance Simplicity WitnessRoot where
