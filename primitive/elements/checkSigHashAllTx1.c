#include "checkSigHashAllTx1.h"

/* A length-prefixed encoding of the following Simplicity program:
 *     Simplicity.Programs.CheckSigHash.checkSigHash' Simplicity.Elements.Programs.CheckSigHashAll.Lib.hashAll
 *     (Simplicity.LibSecp256k1.Spec.PubKey 0x00000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63)
 *     (Simplicity.LibSecp256k1.Spec.Sig 0x00000000000000000000003b78ce563f89a0ed9414f5aa28ad0d96d6795f9c63
 *                                       0x70125c64ce49e44f432ab494e4d44e4424bc48de068b7a918fdcaa31178b1a62)
 * with jets.
 */
const unsigned char elementsCheckSigHashAllTx1[] = {
  0xe8, 0x9d, 0xc6, 0x22, 0x12, 0x40, 0x81, 0x02, 0x04, 0x17, 0x21, 0x02, 0xc8, 0x2b, 0xa0, 0x4a, 0x2a, 0x16, 0x80, 0xb4,
  0x05, 0xb7, 0x40, 0x9a, 0x05, 0x9e, 0xe1, 0x40, 0xb5, 0xf0, 0x01, 0x6c, 0xd4, 0x28, 0x16, 0x01, 0x68, 0xd0, 0x2d, 0x3b,
  0x85, 0x02, 0xe0, 0x5c, 0x08, 0x5c, 0x08, 0x2a, 0x16, 0x61, 0x70, 0x00, 0xb8, 0x78, 0x5c, 0x1b, 0x80, 0x8b, 0x80, 0x05,
  0xc2, 0x38, 0x40, 0x9c, 0x3c, 0x54, 0x2e, 0x1b, 0xc1, 0x85, 0xc0, 0x82, 0xe1, 0x1c, 0x48, 0x2d, 0x01, 0x50, 0xb2, 0x0b,
  0x8a, 0x38, 0x60, 0x98, 0x8b, 0x81, 0xf0, 0x61, 0x40, 0xb6, 0xed, 0x17, 0x16, 0xf1, 0x30, 0x9c, 0x40, 0x2a, 0x16, 0x21,
  0x6a, 0x0b, 0x81, 0xf0, 0x01, 0x71, 0x97, 0x01, 0x14, 0x0b, 0x84, 0x71, 0x00, 0xb8, 0x27, 0x10, 0x8a, 0x05, 0x80, 0x5c,
  0x59, 0xc3, 0x05, 0xc4, 0xdc, 0x46, 0x28, 0x17, 0x0f, 0xe2, 0xc1, 0x71, 0x47, 0x1b, 0x8a, 0x05, 0x80, 0x5a, 0x02, 0xe0,
  0x01, 0x71, 0x30, 0x5c, 0x6d, 0xc8, 0x21, 0x70, 0xf0, 0xb8, 0xd7, 0x88, 0x45, 0xc6, 0xbc, 0x80, 0x14, 0x0b, 0x00, 0xb8,
  0xe3, 0x89, 0x45, 0xc4, 0xdc, 0x6c, 0x28, 0x17, 0x16, 0xf2, 0x18, 0x5c, 0x41, 0xc6, 0xc2, 0x81, 0x60, 0x16, 0x80, 0xb9,
  0x09, 0xc8, 0x01, 0x71, 0xf7, 0x12, 0x8a, 0x05, 0xc8, 0x7e, 0x47, 0x0b, 0x91, 0xbc, 0x87, 0x14, 0x0b, 0x00, 0xb9, 0x25,
  0xc9, 0x21, 0x72, 0x23, 0x8e, 0x85, 0x02, 0xe3, 0x9e, 0x47, 0x0b, 0x8d, 0x39, 0x10, 0x28, 0x16, 0x01, 0x68, 0x0b, 0x80,
  0x05, 0xc7, 0xfc, 0x8d, 0x17, 0x28, 0x79, 0x0a, 0x28, 0x17, 0x25, 0x39, 0x38, 0x2e, 0x4a, 0xf2, 0x44, 0x50, 0x2c, 0x02,
  0xe4, 0x07, 0x24, 0x45, 0xc8, 0x7e, 0x51, 0x8a, 0x05, 0xc9, 0x4e, 0x4d, 0x0b, 0x94, 0x9c, 0x8f, 0x14, 0x0b, 0x00, 0xb4,
  0x05, 0xc9, 0x1e, 0x50, 0x0b, 0x91, 0xfc, 0x92, 0x14, 0x0b, 0x94, 0x7c, 0xa5, 0x17, 0x21, 0xf9, 0x4e, 0x28, 0x16, 0x01,
  0x72, 0x83, 0x96, 0x22, 0x70, 0x01, 0x72, 0x57, 0x92, 0x22, 0xe4, 0x6f, 0x2d, 0x05, 0x02, 0xc0, 0x2c, 0xc2, 0xde, 0x17,
  0x0f, 0x20, 0x5c, 0x9d, 0xe5, 0xc8, 0xb9, 0x41, 0xca, 0x51, 0x40, 0xb9, 0x41, 0xca, 0x01, 0x72, 0xdf, 0x93, 0xa2, 0x81,
  0x60, 0x17, 0x30, 0x5c, 0x9b, 0x17, 0x29, 0xf9, 0x88, 0x14, 0x0b, 0x97, 0xbc, 0xc1, 0x8b, 0x95, 0x1c, 0xaa, 0x14, 0x0b,
  0x00, 0xb4, 0x05, 0xca, 0xee, 0x5c, 0x8b, 0x99, 0x0e, 0x54, 0x8a, 0x05, 0xcb, 0xee, 0x5e, 0x0b, 0x93, 0xc1, 0x50, 0xb9,
  0x89, 0xe6, 0x04, 0x5c, 0x9a, 0x0b, 0x96, 0x1c, 0xc5, 0x09, 0xc1, 0x45, 0x42, 0xc8, 0x2d, 0xa1, 0x73, 0x21, 0xcb, 0xe1,
  0x72, 0xff, 0x96, 0xc2, 0x81, 0x72, 0xe3, 0x97, 0x02, 0xe4, 0xa8, 0x54, 0x2e, 0x5d, 0xf2, 0xd8, 0x5c, 0xc7, 0xf3, 0x26,
  0x28, 0x17, 0x30, 0x5c, 0xb9, 0x13, 0x94, 0x22, 0xa1, 0x66, 0x17, 0x32, 0x7c, 0xce, 0x0b, 0x91, 0xe1, 0x73, 0x1f, 0xcc,
  0xd8, 0xb9, 0x98, 0xe6, 0x24, 0x50, 0x2c, 0x02, 0xe6, 0x7f, 0x9a, 0x01, 0x72, 0x14, 0x2e, 0x67, 0x79, 0x85, 0x17, 0x34,
  0x7c, 0xd3, 0x0a, 0x05, 0x80, 0x59, 0x85, 0xb8, 0x2e, 0x18, 0xb8, 0xb9, 0x14, 0x0b, 0x06, 0xa0, 0x22, 0xd8, 0x9c, 0xe1,
  0x0b, 0x9b, 0x9e, 0x70, 0x05, 0xcb, 0xc0, 0xb9, 0x7d, 0xc3, 0x45, 0x02, 0xe6, 0xa3, 0x9b, 0x71, 0x73, 0x5f, 0xcd, 0xb0,
  0xa0, 0x5c, 0xd0, 0x73, 0x70, 0x27, 0x34, 0x02, 0xa1, 0x66, 0x17, 0x35, 0xfc, 0xd6, 0x8b, 0x9b, 0x6e, 0x71, 0x45, 0x02,
  0xe6, 0xe3, 0x9a, 0xb1, 0x39, 0x3a, 0x2a, 0x17, 0x36, 0xbc, 0xda, 0x89, 0xc8, 0x01, 0x73, 0x4f, 0xcd, 0x80, 0xb9, 0x52,
  0x15, 0x0b, 0x20, 0xb6, 0x85, 0xcd, 0xd7, 0x39, 0x02, 0xe5, 0x30, 0x5c, 0xa2, 0xe6, 0x48, 0x50, 0x2e, 0x70, 0x39, 0xd5,
  0x17, 0x18, 0x85, 0xce, 0x17, 0x3b, 0x22, 0xe6, 0xf3, 0x9d, 0x01, 0x40, 0xb0, 0x0b, 0x30, 0xb9, 0xc5, 0xe7, 0x00, 0x5c,
  0xe4, 0x73, 0xa2, 0x28, 0x17, 0x37, 0xfc, 0xef, 0x8b, 0x83, 0x05, 0x42, 0xe7, 0x6f, 0x99, 0x81, 0x73, 0xaf, 0xce, 0xb8,
  0xb9, 0x97, 0x0a, 0x85, 0x88, 0x5b, 0x02, 0xe1, 0x03, 0x35, 0x43, 0x90, 0x60, 0xb9, 0xe8, 0xe7, 0xd4, 0x4e, 0x7d, 0x44,
  0xe7, 0xd4, 0x4e, 0x7f, 0x44, 0xe7, 0xf4, 0x5c, 0xaa, 0xe7, 0xe4, 0x5c, 0xfc, 0x85, 0xd0, 0x02, 0x17, 0x40, 0x08, 0x58,
  0x8e, 0x16, 0xc0, 0xb7, 0x80, 0xe4, 0x30, 0x78, 0x18, 0x1c, 0x85, 0x4f, 0xb2, 0x27, 0x02, 0x13, 0xa0, 0x18, 0x4e, 0x80,
  0xe1, 0x3a, 0x03, 0x85, 0xd0, 0x17, 0xcf, 0xf0, 0xb9, 0x78, 0x17, 0x40, 0x58, 0x5d, 0x02, 0x61, 0x74, 0x09, 0x85, 0x90,
  0x5b, 0x02, 0xe2, 0x10, 0x1c, 0x97, 0x17, 0x00, 0x0b, 0x93, 0x00, 0x39, 0x35, 0x48, 0x27, 0x40, 0xda, 0x48, 0x10, 0x20,
  0x40, 0x81, 0x02, 0x04, 0x17, 0x48, 0x9a, 0x44, 0x0b, 0x48, 0x5a, 0x42, 0xd2, 0x16, 0x90, 0xb4, 0x85, 0xa4, 0x27, 0x1c,
  0x1c, 0x2d, 0x7a, 0xc5, 0xac, 0x2e, 0x06, 0x17, 0x03, 0x0b, 0x81, 0x85, 0xc0, 0xc2, 0xe0, 0x61, 0x70, 0x30, 0x9c, 0x82,
  0x38, 0x3a, 0xc6, 0x0b, 0xa0, 0xf7, 0xa0, 0xf4, 0x5d, 0x07, 0x3c, 0xd5, 0x0b, 0xa0, 0xe4, 0x2e, 0x84, 0x10, 0xba, 0x10,
  0x42, 0xc4, 0x70, 0x9c, 0x8c, 0x0e, 0x90, 0x38, 0xa8, 0x2e, 0x49, 0x00, 0xe6, 0x20, 0x5c, 0x8c, 0xd8, 0x2e, 0x84, 0x6e,
  0x81, 0xa1, 0x3a, 0x11, 0x85, 0xd0, 0x8c, 0x17, 0x42, 0x70, 0x5d, 0x09, 0xc1, 0x70, 0x20, 0xb3, 0x0b, 0x48, 0x0e, 0x64,
  0xa9, 0x44, 0xe8, 0x53, 0x17, 0x17, 0x71, 0xb0, 0xb8, 0xd8, 0x2e, 0x36, 0x0b, 0x8d, 0x82, 0xe3, 0x60, 0xb8, 0xd8, 0x2e,
  0x36, 0x09, 0xca, 0x53, 0x85, 0xc8, 0x0e, 0x38, 0x17, 0x1c, 0x05, 0xc8, 0x00, 0xb9, 0x00, 0x17, 0x20, 0x02, 0xe4, 0x00,
  0x5c, 0x80, 0x0b, 0x90, 0x01, 0x39, 0x5e, 0x70, 0x75, 0x8c, 0x3f, 0x14, 0x1f, 0x8b, 0x8f, 0xd0, 0xd8, 0x83, 0x05, 0x42,
  0xc4, 0x2c, 0xc1, 0xd2, 0x07, 0x0f, 0x0b, 0x97, 0xe0, 0x39, 0xb5, 0x13, 0x89, 0x80, 0xe6, 0xdc, 0x5c, 0x4c, 0x17, 0x27,
  0xc0, 0x73, 0x75, 0x01, 0x02, 0x28, 0xa0, 0x13, 0x98, 0x41, 0x50, 0x9c, 0x84, 0x17, 0x43, 0x57, 0x43, 0xf0, 0xb9, 0x68,
  0x17, 0x43, 0xf0, 0x5d, 0x10, 0xc1, 0x74, 0x43, 0x05, 0xc8, 0xa0, 0xb3, 0x0b, 0x78, 0x0e, 0x72, 0x87, 0xd0, 0x10, 0x17,
  0x40, 0x50, 0x0e, 0x73, 0x45, 0xd1, 0x15, 0xd0, 0xce, 0x27, 0x44, 0x50, 0xba, 0x22, 0x82, 0xe8, 0x92, 0x0b, 0xa2, 0x48,
  0x2e, 0x4b, 0x05, 0xc8, 0xb0, 0xb4, 0x00, 0xe7, 0x58, 0x5d, 0x0a, 0x47, 0x14, 0x6c, 0x40, 0x8f, 0x48, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xed, 0xe3, 0x39, 0x58, 0xfe, 0x26, 0x83, 0xb6, 0x50, 0x53, 0xd6,
  0xa8, 0xa2, 0xb4, 0x36, 0x5b, 0x59, 0xe5, 0x7e, 0x71, 0x8d, 0xc0, 0x49, 0x71, 0x93, 0x39, 0x27, 0x91, 0x3d, 0x0c, 0xaa,
  0xd2, 0x53, 0x93, 0x51, 0x39, 0x10, 0x92, 0xf1, 0x23, 0x78, 0x1a, 0x2d, 0xea, 0x46, 0x3f, 0x72, 0xa8, 0xc4, 0x5e, 0x2c,
  0x69, 0x88
};

const size_t sizeof_elementsCheckSigHashAllTx1 = sizeof(elementsCheckSigHashAllTx1);

/* The commitment Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_cmr[] = {
  0x526ca605u, 0xca9ec510u, 0xa064eef2u, 0x60178478u, 0xe3cf40e1u, 0x4167d973u, 0x5c4e0f0fu, 0xb6939056u
};

/* The identity Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_imr[] = {
  0xae8d39a4u, 0x2aad19a4u, 0x5bc8b61du, 0x0a360475u, 0x41a1dc85u, 0x280deeccu, 0xa24e5ae3u, 0x4fe2d675u
};

/* The annotated Merkle root of the above elementsCheckSigHashAllTx1 Simplicity expression. */
const uint32_t elementsCheckSigHashAllTx1_amr[] = {
  0xed4bc061u, 0xfdf902acu, 0xe000993cu, 0x3ed16714u, 0x404adfaau, 0xa7eeda9fu, 0x39c73776u, 0x441a4ba7u
};
