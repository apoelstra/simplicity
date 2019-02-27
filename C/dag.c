#include "dag.h"

#include <assert.h>
#include <stdbool.h>
#include "bounded.h"
#include "tag.h"
#include "uword.h"

/* :TODO: remove these includes after witnesses are supported, etc. */
#include <stdio.h>
#include <stdlib.h>

/* Prepends Simplicity tag prefixes to a string literal 's'. */
#define COMMITMENT_TAG(s) "Simplicity\x1F" "Commitment\x1F" s
#define WITNESS_TAG(s) "Simplicity\x1F" "Witness\x1F" s

/* Given a tag for a core or witness expression node, return the SHA-256 hash of its assocaited CMR tag.
 * This is the "initial value" for computing the commitment Merkle root for that expression.
 *
 * Precondition: 'tag' is a valid tag;
 *               HIDDEN != 'tag'
 */
static sha256_midstate cmrIV(int32_t tag) {
  /* Cache the initial values for all the tags. */
  static bool static_initialized = false;
  static sha256_midstate compIV,
                         caseIV,
                         pairIV,
                         disconnectIV,
                         injlIV,
                         injrIV,
                         takeIV,
                         dropIV,
                         idenIV,
                         unitIV,
                         witnessIV;
  if (!static_initialized) {
    MK_TAG(compIV.s, COMMITMENT_TAG("comp"));
    MK_TAG(caseIV.s, COMMITMENT_TAG("case"));
    MK_TAG(pairIV.s, COMMITMENT_TAG("pair"));
    MK_TAG(disconnectIV.s, COMMITMENT_TAG("disconnect"));
    MK_TAG(injlIV.s, COMMITMENT_TAG("injl"));
    MK_TAG(injrIV.s, COMMITMENT_TAG("injr"));
    MK_TAG(takeIV.s, COMMITMENT_TAG("take"));
    MK_TAG(dropIV.s, COMMITMENT_TAG("drop"));
    MK_TAG(idenIV.s, COMMITMENT_TAG("iden"));
    MK_TAG(unitIV.s, COMMITMENT_TAG("unit"));
    MK_TAG(witnessIV.s, COMMITMENT_TAG("witness"));
    static_initialized = true;
  }

  switch (tag) {
   case COMP: return compIV;
   case ASSERTL:
   case ASSERTR:
   case CASE: return caseIV;
   case PAIR: return pairIV;
   case DISCONNECT: return disconnectIV;
   case INJL: return injlIV;
   case INJR: return injrIV;
   case TAKE: return takeIV;
   case DROP: return dropIV;
   case IDEN: return idenIV;
   case UNIT: return unitIV;
   case WITNESS: return witnessIV;
  }
  /* Precondition violated. */
  assert(false);
  return (sha256_midstate){0};
}

/* Given a tag for a core or witness expression node, return the SHA-256 hash of its assocaited WMR tag.
 * This is the "initial value" for computing the witness Merkle root for that expression.
 *
 * Precondition: 'tag' is a valid tag;
 *               HIDDEN != 'tag'
 */
static sha256_midstate wmrIV(int32_t tag) {
  /* Cache the initial values for all the tags. */
  static bool static_initialized = false;
  static sha256_midstate compIV,
                         assertlIV,
                         assertrIV,
                         caseIV,
                         pairIV,
                         disconnectIV,
                         injlIV,
                         injrIV,
                         takeIV,
                         dropIV,
                         idenIV,
                         unitIV,
                         witnessIV;
  if (!static_initialized) {
    MK_TAG(compIV.s, WITNESS_TAG("comp"));
    MK_TAG(assertlIV.s, WITNESS_TAG("assertl"));
    MK_TAG(assertrIV.s, WITNESS_TAG("assertr"));
    MK_TAG(caseIV.s, WITNESS_TAG("case"));
    MK_TAG(pairIV.s, WITNESS_TAG("pair"));
    MK_TAG(disconnectIV.s, WITNESS_TAG("disconnect"));
    MK_TAG(injlIV.s, WITNESS_TAG("injl"));
    MK_TAG(injrIV.s, WITNESS_TAG("injr"));
    MK_TAG(takeIV.s, WITNESS_TAG("take"));
    MK_TAG(dropIV.s, WITNESS_TAG("drop"));
    MK_TAG(idenIV.s, WITNESS_TAG("iden"));
    MK_TAG(unitIV.s, WITNESS_TAG("unit"));
    MK_TAG(witnessIV.s, WITNESS_TAG("witness"));
    static_initialized = true;
  }

  switch (tag) {
   case COMP: return compIV;
   case ASSERTL: return assertlIV;
   case ASSERTR: return assertrIV;
   case CASE: return caseIV;
   case PAIR: return pairIV;
   case DISCONNECT: return disconnectIV;
   case INJL: return injlIV;
   case INJR: return injrIV;
   case TAKE: return takeIV;
   case DROP: return dropIV;
   case IDEN: return idenIV;
   case UNIT: return unitIV;
   case WITNESS: return witnessIV;
  }
  /* Precondition violated. */
  assert(false);
  return (sha256_midstate){0};
}

/* Given a well-formed dag representing a Simplicity expression, compute the commitment Merkle roots of all subexpressions.
 * For all 'i', 0 <= 'i' < 'len', 'analysis[i].commitmentMerkleRoot' will be the CMR of the subexpression denoted by the slice
 *
 *     (dag_nodes[i + 1])dag.
 *
 * The CMR of the overall expression will be 'analysis[len - 1].commitmentMerkleRoot'.
 *
 * Precondition: analyses analysis[len];
 *               dag_node dag[len] and 'dag' is well-formed.
 */
void computeCommitmentMerkleRoot(analyses* analysis, const dag_node* dag, const size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (HIDDEN == dag[i].tag) {
      analysis[i].commitmentMerkleRoot = dag[i].hash;
    } else {
      analysis[i].commitmentMerkleRoot = cmrIV(dag[i].tag);

      /* Hash the child sub-expression's CMRs (if there are any children). */
      uint32_t block[16] = {0};
      size_t j = 8;
      switch (dag[i].tag) {
       case COMP:
       case ASSERTL:
       case ASSERTR:
       case CASE:
       case PAIR:
        memcpy(block + j, analysis[dag[i].child[1]].commitmentMerkleRoot.s, sizeof(uint32_t[8]));
        j = 0;
        /* Fall through. */
       case DISCONNECT: /* Only the first child is used in the CMR. */
       case INJL:
       case INJR:
       case TAKE:
       case DROP:
        memcpy(block + j, analysis[dag[i].child[0]].commitmentMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].commitmentMerkleRoot.s, block);
      }
    }
  }
}

/* Given a well-typed dag representing a Simplicity expression, compute the witness Merkle roots of all subexpressions.
 * For all 'i', 0 <= 'i' < 'len', 'analysis[i].witnessMerkleRoot' will be the WMR of the subexpression denoted by the slice
 *
 *     (dag_nodes[i + 1])dag.
 *
 * The WMR of the overall expression will be 'analysis[len - 1].witnessMerkleRoot'.
 *
 * Precondition: analyses analysis[len];
 *               dag_node dag[len] and 'dag' is well-typed with 'type_dag'.
 */
void computeWitnessMerkleRoot(analyses* analysis, const dag_node* dag, const type* type_dag, const size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (HIDDEN == dag[i].tag) {
      analysis[i].witnessMerkleRoot = dag[i].hash;
    } else {
      analysis[i].witnessMerkleRoot = wmrIV(dag[i].tag);

      uint32_t block[16] = {0};
      switch (dag[i].tag) {
       case ASSERTL:
       case ASSERTR:
       case CASE:
       case DISCONNECT:
        memcpy(block, type_dag[dag[i].typeAnnotation[0]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[1]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        memcpy(block, type_dag[dag[i].typeAnnotation[2]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[3]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        memcpy(block, analysis[dag[i].child[0]].witnessMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, analysis[dag[i].child[1]].witnessMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        break;
       case COMP:
       case PAIR:
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[0]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        memcpy(block, type_dag[dag[i].typeAnnotation[1]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[2]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        memcpy(block, analysis[dag[i].child[0]].witnessMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, analysis[dag[i].child[1]].witnessMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        break;
       case INJL:
       case INJR:
       case TAKE:
       case DROP:
        memcpy(block, type_dag[dag[i].typeAnnotation[0]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[1]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        memcpy(block, type_dag[dag[i].typeAnnotation[2]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        memcpy(block + 8, analysis[dag[i].child[0]].witnessMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        break;
       case IDEN:
       case UNIT:
        memcpy(block + 8, type_dag[dag[i].typeAnnotation[0]].typeMerkleRoot.s, sizeof(uint32_t[8]));
        sha256_compression(analysis[i].witnessMerkleRoot.s, block);
        break;
       case WITNESS:
        /* :TODO: Support witness */
        fprintf(stderr, "Witness Merkle root for witness not yet implemented\n");
        exit(EXIT_FAILURE);
        break;
      }
    }
  }
}

/* :TODO: Document extraStackBoundTCO in the Tech Report (and implement it in Haskell) */
/* Given a well-typed dag representing a Simplicity expression, compute the bounds on memory requirement for evaluation.
 * For all 'i', 0 <= 'i' < 'len', compute 'analysis[i].extraCellsBoundTCO' and 'analysis[i].extraStackBoundTCO'
 * for the subexpression denoted by the slice
 *
 *     (dag_nodes[i + 1])dag.
 *
 * Precondition: analyses analysis[len];
 *               dag_node dag[len] and 'dag' is well-typed with 'type_dag'.
 * Postcondition: 'max(analysis[len-1].extraCellsBoundTCO[0], analysis[len-1].extraCellsBoundTCO[1]) == SIZE_MAX'.
 *                  or 'analysis[len-1].extraCellsBoundTCO' characterizes the number of UWORDs needed
 *                    for the frames allocated during evaluation of 'dag';
 *                analysis[len-1].extraStackBoundTCO[0] bounds the the number of stack frames needed during execution of 'dag';
 */
void computeEvalTCOBounds(analyses* analysis, const dag_node* dag, const type* type_dag, const size_t len) {
  size_t scratch;
  for (size_t i = 0; i < len; ++i) {
    switch (dag[i].tag) {
     case ASSERTL:
     case ASSERTR:
     case CASE:
      analysis[i].extraCellsBoundTCO[0] = max( analysis[dag[i].child[0]].extraCellsBoundTCO[0]
                                             , analysis[dag[i].child[1]].extraCellsBoundTCO[0] );
      analysis[i].extraCellsBoundTCO[1] = max( analysis[dag[i].child[0]].extraCellsBoundTCO[1]
                                             , analysis[dag[i].child[1]].extraCellsBoundTCO[1] );

      analysis[i].extraStackBound[0] = max( analysis[dag[i].child[0]].extraStackBound[0]
                                          , analysis[dag[i].child[1]].extraStackBound[0] );
      analysis[i].extraStackBound[1] = max( analysis[dag[i].child[0]].extraStackBound[1]
                                          , analysis[dag[i].child[1]].extraStackBound[1] );
      break;
     case DISCONNECT:
      /* :TODO: Support disconnect */
      fprintf(stderr, "EvalTCOBounds for disconnect not yet implemented\n");
      exit(EXIT_FAILURE);
      break;
     case COMP:
      /* :TODO: replace this check with a consensus critical limit. */
      if (UWORD_BIT - 1 <= SIZE_MAX - type_dag[dag[i].typeAnnotation[1]].bitSize) {
        scratch = roundUWord(type_dag[dag[i].typeAnnotation[1]].bitSize);
        analysis[i].extraCellsBoundTCO[0] = max( bounded_add( scratch
                                                            , max( analysis[dag[i].child[0]].extraCellsBoundTCO[0]
                                                                 , analysis[dag[i].child[1]].extraCellsBoundTCO[1] ))
                                               , analysis[dag[i].child[1]].extraCellsBoundTCO[0] );
        analysis[i].extraCellsBoundTCO[1] = bounded_add(scratch, analysis[dag[i].child[0]].extraCellsBoundTCO[1]);

      } else {
        /* 'type_dag[dag[i].typeAnnotation[1]].bitSize' has exceeded our limits. */
        analysis[i].extraCellsBoundTCO[0] = SIZE_MAX;
        analysis[i].extraCellsBoundTCO[1] = SIZE_MAX;
      }
      analysis[i].extraStackBound[0] = max( analysis[dag[i].child[0]].extraStackBound[0]
                                          , analysis[dag[i].child[1]].extraStackBound[1] );
      bounded_inc(&analysis[i].extraStackBound[0]);
      scratch = analysis[dag[i].child[0]].extraStackBound[1];
      bounded_inc(&scratch);
      analysis[i].extraStackBound[1] = max( scratch
                                          , analysis[dag[i].child[1]].extraStackBound[1] );
      break;
     case PAIR:
      analysis[i].extraCellsBoundTCO[0] = analysis[dag[i].child[1]].extraCellsBoundTCO[0];
      analysis[i].extraCellsBoundTCO[1] = max( analysis[dag[i].child[0]].extraCellsBoundTCO[0]
                                             , max( analysis[dag[i].child[0]].extraCellsBoundTCO[1]
                                                  , analysis[dag[i].child[1]].extraCellsBoundTCO[1] ));

      analysis[i].extraStackBound[0] = max( analysis[dag[i].child[0]].extraStackBound[0]
                                          , analysis[dag[i].child[1]].extraStackBound[0] );
      analysis[i].extraStackBound[1] = max( analysis[dag[i].child[0]].extraStackBound[0]
                                          , analysis[dag[i].child[1]].extraStackBound[1] );
      break;
     case INJL:
     case INJR:
     case TAKE:
     case DROP:
      analysis[i].extraCellsBoundTCO[0] = analysis[dag[i].child[0]].extraCellsBoundTCO[0];
      analysis[i].extraCellsBoundTCO[1] = analysis[dag[i].child[0]].extraCellsBoundTCO[1];
      analysis[i].extraStackBound[0] = analysis[dag[i].child[0]].extraStackBound[0];
      analysis[i].extraStackBound[1] = analysis[dag[i].child[0]].extraStackBound[1];
      break;
     default:
      analysis[i].extraCellsBoundTCO[0] = analysis[i].extraCellsBoundTCO[1] = 0;
      analysis[i].extraStackBound[0] = analysis[i].extraStackBound[1] = 0;
    }
  }
}
