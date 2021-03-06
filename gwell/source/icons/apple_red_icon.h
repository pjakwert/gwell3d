#include "icons.h"


const QImage* Icons::appleRedIcon()
{
  const unsigned char apple_data[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x57, 0x02, 0xf9, 0x87, 0x00, 0x00, 0x0a,
    0xc2, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x99, 0xdb, 0x8f, 0x5d,
    0xd7, 0x5d, 0xc7, 0x3f, 0xbf, 0xb5, 0xf6, 0x3e, 0xe7, 0x8c, 0x67, 0xec,
    0x71, 0xec, 0x34, 0x37, 0x92, 0x10, 0x42, 0xa3, 0x14, 0x55, 0x91, 0x40,
    0x7d, 0x40, 0xb5, 0xf2, 0xc8, 0xff, 0xd0, 0x07, 0x52, 0x2e, 0x02, 0xda,
    0xb4, 0x2a, 0x51, 0x8a, 0x84, 0x68, 0x41, 0xa8, 0x34, 0x8d, 0xd2, 0x36,
    0xb4, 0x6a, 0x04, 0xca, 0xa5, 0x0e, 0x15, 0x82, 0x42, 0xaa, 0xbe, 0x94,
    0x07, 0x24, 0x9e, 0x2a, 0x21, 0x2e, 0x32, 0x11, 0x8a, 0x0a, 0x0a, 0x45,
    0x69, 0xa9, 0x51, 0xa0, 0x71, 0x6a, 0xe3, 0xda, 0x1e, 0xcf, 0xcc, 0x39,
    0x67, 0xef, 0xbd, 0xd6, 0xef, 0xc2, 0xc3, 0x8e, 0xdd, 0x38, 0x1d, 0xcf,
    0x78, 0xdc, 0x46, 0x51, 0xa5, 0x7c, 0x5f, 0xce, 0xc3, 0xd9, 0x7b, 0xaf,
    0xdf, 0xf7, 0x77, 0xfd, 0xae, 0xb5, 0xe4, 0xc4, 0x89, 0x13, 0xfc, 0x24,
    0x23, 0xbd, 0xd5, 0x06, 0xfc, 0xa8, 0x78, 0x9b, 0xc0, 0x5b, 0x8d, 0xb7,
    0x09, 0xbc, 0xd5, 0x68, 0xae, 0xf5, 0xc1, 0x67, 0xfe, 0xea, 0x4f, 0x43,
    0x24, 0x01, 0x41, 0x04, 0x3c, 0xf8, 0xc0, 0x47, 0x64, 0xaf, 0x77, 0x3e,
    0xf7, 0xe8, 0xef, 0xc4, 0xd7, 0xfe, 0xee, 0x79, 0x4e, 0x9c, 0x38, 0xb1,
    0xe7, 0xb3, 0xd7, 0x8b, 0x6b, 0x8a, 0xc0, 0xb3, 0x5f, 0x7d, 0x2a, 0x0e,
    0xdf, 0x30, 0xe5, 0x5d, 0xf7, 0x1d, 0xe5, 0x8e, 0x9f, 0x5d, 0x67, 0x3a,
    0xcb, 0x7c, 0xf1, 0xaf, 0x9f, 0x8c, 0xdd, 0xde, 0x79, 0xf2, 0xf3, 0x1f,
    0x8f, 0x13, 0x2f, 0x7c, 0xeb, 0xc7, 0x63, 0xe5, 0x2e, 0xd8, 0x93, 0xc0,
    0xb3, 0x5f, 0x79, 0x2a, 0x56, 0x66, 0x0d, 0x47, 0x6f, 0x5e, 0xe3, 0xdc,
    0xd9, 0x05, 0xb5, 0x18, 0xf7, 0xbe, 0xfb, 0x1d, 0xdc, 0x7d, 0xef, 0xe1,
    0x5d, 0x49, 0x5c, 0xdc, 0x9c, 0x73, 0xe6, 0xec, 0xc5, 0x37, 0xd5, 0xfb,
    0xb0, 0x07, 0x81, 0xe3, 0xcf, 0x3d, 0x19, 0x07, 0xd6, 0x1a, 0x8e, 0xbc,
    0x63, 0x85, 0x8d, 0x73, 0x4b, 0x96, 0x0b, 0x65, 0xb9, 0xad, 0xbc, 0x7c,
    0x72, 0x83, 0xf3, 0xdf, 0xef, 0xb9, 0xe1, 0xc6, 0x19, 0xc7, 0x9f, 0xfb,
    0x61, 0x12, 0x4f, 0x7e, 0xfe, 0xe3, 0xf1, 0x8f, 0xcf, 0xff, 0xe7, 0x9b,
    0x67, 0xf5, 0xeb, 0x70, 0xd5, 0x1a, 0x38, 0xfe, 0xdc, 0x93, 0xd1, 0x34,
    0xc2, 0x4f, 0xdf, 0x7d, 0x03, 0xa7, 0x5f, 0xdd, 0xc6, 0x34, 0x38, 0xb4,
    0x3e, 0xe5, 0xd6, 0xdb, 0x0f, 0x31, 0xf4, 0x4a, 0xd3, 0x26, 0xdc, 0x83,
    0xf5, 0xc3, 0x33, 0x9e, 0xfd, 0xca, 0x53, 0x61, 0xa6, 0x3c, 0xf8, 0xc0,
    0x43, 0x02, 0xb0, 0x71, 0x71, 0xce, 0xf6, 0xbc, 0x7f, 0xd3, 0xbd, 0xbf,
    0x2b, 0x01, 0x49, 0xc2, 0x6d, 0x77, 0x1e, 0xe4, 0xd4, 0x77, 0x37, 0x59,
    0x3b, 0x38, 0xe1, 0xf0, 0xed, 0x6b, 0x9c, 0x7e, 0x65, 0xce, 0x2b, 0xff,
    0x73, 0x81, 0x32, 0x28, 0xdb, 0x9b, 0x05, 0x33, 0x10, 0x49, 0x88, 0x8c,
    0xbf, 0x4f, 0x7f, 0xf9, 0x89, 0xf8, 0xd0, 0xfb, 0x1f, 0x96, 0x8d, 0xcd,
    0xf9, 0x9b, 0x6d, 0xf7, 0xee, 0x04, 0xbe, 0xf4, 0xd5, 0xa7, 0xe3, 0x86,
    0xa3, 0x33, 0xb6, 0x2e, 0x0e, 0xdc, 0x78, 0xd3, 0x0a, 0x67, 0x4e, 0x2d,
    0x38, 0xb0, 0xd6, 0x32, 0x9f, 0xf7, 0x0c, 0x9d, 0x32, 0x76, 0xa3, 0xc4,
    0x87, 0xde, 0xff, 0x83, 0x4e, 0xf4, 0xd4, 0x5f, 0x7e, 0x21, 0x52, 0x6a,
    0x78, 0xfa, 0xcb, 0x4f, 0xc4, 0xf6, 0xa2, 0xbf, 0xe2, 0x7b, 0x2f, 0xfc,
    0xc9, 0xe3, 0x31, 0xed, 0x15, 0x55, 0xc7, 0x52, 0x50, 0xad, 0x52, 0xbb,
    0x4a, 0x27, 0x95, 0x0b, 0x5a, 0xd8, 0xe8, 0x2b, 0x1f, 0xfe, 0xc2, 0xd3,
    0xd7, 0x15, 0xad, 0x1d, 0x09, 0x34, 0x6d, 0x22, 0x25, 0xc1, 0x7d, 0xf4,
    0x6c, 0x10, 0x7c, 0xeb, 0xc5, 0x33, 0xa4, 0xd4, 0x5c, 0x4e, 0x93, 0x37,
    0xe2, 0xc3, 0xbf, 0xf2, 0x51, 0x19, 0x89, 0x3c, 0x11, 0xdf, 0x79, 0xf9,
    0x34, 0x27, 0x4e, 0x9c, 0x90, 0x17, 0x1f, 0xff, 0x6c, 0x1c, 0x6a, 0xe1,
    0x96, 0x94, 0x88, 0x03, 0x33, 0x70, 0x70, 0x57, 0xba, 0x2e, 0xa1, 0x2b,
    0x99, 0xa5, 0xc3, 0xc1, 0x94, 0x39, 0xb2, 0x3a, 0xe3, 0x6f, 0xfe, 0xf0,
    0xa1, 0xd8, 0x1c, 0x06, 0x7e, 0xed, 0xf1, 0x2f, 0xee, 0x8b, 0x88, 0xbc,
    0x51, 0x8d, 0xfe, 0xc5, 0xd7, 0x9e, 0x89, 0x43, 0xeb, 0x13, 0x0e, 0x1f,
    0x9d, 0x71, 0xf6, 0xf4, 0x92, 0x8b, 0x1b, 0x1d, 0xe1, 0x20, 0x22, 0x7c,
    0xf0, 0x97, 0x7f, 0xe0, 0xf1, 0x7f, 0x7b, 0xe4, 0xd1, 0x58, 0x91, 0x19,
    0xad, 0x54, 0x14, 0x27, 0x42, 0x30, 0x81, 0x5e, 0x0a, 0xa1, 0xc1, 0x2d,
    0x07, 0x0f, 0x30, 0x99, 0x34, 0xb4, 0x4d, 0x4b, 0x4a, 0x89, 0xc8, 0x02,
    0x0a, 0xda, 0x17, 0x6c, 0xa8, 0x54, 0x0b, 0xba, 0xaa, 0x74, 0xb2, 0xa4,
    0x6f, 0x13, 0x17, 0xfb, 0x9e, 0x85, 0x75, 0x6c, 0xaa, 0x31, 0x68, 0xe5,
    0x83, 0x7f, 0xfc, 0x67, 0xd7, 0x44, 0xe4, 0x0a, 0x02, 0xcf, 0xfd, 0xed,
    0xf1, 0x68, 0xda, 0x4c, 0x6e, 0xe0, 0xfc, 0xd9, 0x0e, 0x77, 0x07, 0x84,
    0x07, 0x1f, 0xf8, 0xed, 0xcb, 0x1f, 0xfb, 0xaf, 0x4f, 0x7d, 0x3a, 0x66,
    0xcd, 0x94, 0x59, 0x13, 0x4c, 0x52, 0x43, 0xce, 0x82, 0x48, 0x60, 0x4d,
    0x90, 0x48, 0xa4, 0x48, 0xa4, 0x0c, 0xd1, 0x66, 0x9a, 0x66, 0x6c, 0x72,
    0xa9, 0x69, 0x50, 0x75, 0xb4, 0x28, 0x56, 0x2a, 0xd6, 0x0d, 0x24, 0x87,
    0xbe, 0x14, 0xb6, 0xa5, 0xd2, 0xe5, 0xa0, 0xf3, 0xca, 0x86, 0x57, 0xb6,
    0xfb, 0x8e, 0x85, 0x56, 0x4c, 0x8c, 0xdf, 0xf8, 0xcc, 0xde, 0x24, 0xae,
    0x48, 0xa1, 0xe9, 0xac, 0xe1, 0xe2, 0xc6, 0x92, 0x5a, 0x7c, 0xc7, 0x54,
    0xf9, 0xef, 0x47, 0x1e, 0x8b, 0xd5, 0xd9, 0x8c, 0xb5, 0xc9, 0x8c, 0x76,
    0x9a, 0x99, 0x06, 0x4c, 0x8e, 0xac, 0x93, 0x57, 0x56, 0xe9, 0x36, 0xcf,
    0xd3, 0xd0, 0x90, 0x50, 0x48, 0x09, 0x52, 0x42, 0x92, 0x61, 0x22, 0xd0,
    0x24, 0x9a, 0x6a, 0x74, 0x04, 0xe2, 0x46, 0x6a, 0x5b, 0x62, 0x18, 0x68,
    0x57, 0x5a, 0x0e, 0xf4, 0x82, 0x79, 0xa5, 0xe4, 0x96, 0x26, 0x8c, 0x59,
    0x6e, 0x18, 0x4a, 0xa5, 0x2f, 0xc1, 0xb3, 0xbf, 0xf7, 0x81, 0xf8, 0xad,
    0xcf, 0x1e, 0xdf, 0x95, 0xc4, 0x15, 0x04, 0x36, 0x2e, 0x2c, 0xf9, 0xcd,
    0xf7, 0xed, 0x2c, 0x11, 0x5e, 0x7a, 0xe4, 0xb1, 0xb8, 0x71, 0x6d, 0x8d,
    0x95, 0xd5, 0x29, 0xeb, 0x37, 0xdf, 0xca, 0xe1, 0xbb, 0x7e, 0x86, 0xf5,
    0xfb, 0xde, 0x4d, 0xb9, 0x70, 0x01, 0xb4, 0xb2, 0x75, 0xf2, 0x24, 0xfd,
    0x99, 0xef, 0x21, 0x34, 0x24, 0x49, 0x18, 0x41, 0x4a, 0x2d, 0x39, 0x0b,
    0xea, 0x4e, 0xcd, 0x41, 0x6a, 0x41, 0x2c, 0x88, 0x2a, 0xb8, 0x08, 0x8d,
    0x3a, 0x6d, 0x16, 0x56, 0x11, 0x4a, 0xa7, 0x34, 0x4d, 0xc2, 0xc8, 0x34,
    0x93, 0xd1, 0xac, 0xea, 0x3d, 0xc7, 0x3f, 0xf6, 0xeb, 0xf1, 0x81, 0xcf,
    0xfc, 0xf9, 0x55, 0x49, 0xfc, 0x50, 0x0d, 0xec, 0x84, 0x7f, 0x7d, 0xf4,
    0x93, 0x71, 0xe7, 0xea, 0x21, 0x0e, 0x4e, 0xa7, 0xdc, 0xf1, 0x8b, 0xef,
    0xe5, 0xf0, 0x7b, 0x7e, 0x9e, 0xd9, 0xfa, 0x11, 0xca, 0xc5, 0x73, 0x0c,
    0xe7, 0x37, 0xa8, 0x1b, 0x1b, 0x2c, 0xbe, 0xfd, 0x6d, 0x82, 0x0a, 0x91,
    0x08, 0x33, 0x48, 0xa0, 0xc9, 0x21, 0x1c, 0x73, 0xc1, 0x74, 0xa0, 0x68,
    0xa1, 0x0e, 0x03, 0xd6, 0x0d, 0x78, 0x71, 0xac, 0x18, 0x9a, 0x60, 0xd9,
    0x17, 0x96, 0xda, 0x33, 0x07, 0x2e, 0x44, 0xcf, 0xbc, 0xf4, 0xcc, 0xa3,
    0xb0, 0xbd, 0x18, 0xc8, 0x39, 0xb3, 0x7a, 0xa0, 0xe5, 0x57, 0x3f, 0xf5,
    0xcc, 0x8e, 0x24, 0xae, 0x49, 0xcc, 0xdd, 0xbe, 0x72, 0x80, 0xd5, 0x69,
    0xcb, 0x8d, 0x77, 0xdd, 0xc5, 0xda, 0xbb, 0xee, 0x25, 0x37, 0x53, 0x6c,
    0xe8, 0xa8, 0x5b, 0xdb, 0xf4, 0x9b, 0xe7, 0xa8, 0xa7, 0x5e, 0x85, 0x59,
    0x43, 0x93, 0x57, 0xa9, 0xd6, 0x91, 0x34, 0x13, 0x66, 0xb4, 0x59, 0xa8,
    0xe1, 0xc4, 0x60, 0x58, 0x23, 0x78, 0x38, 0x00, 0xb6, 0xd2, 0x22, 0xb9,
    0x22, 0x38, 0x0c, 0x95, 0x36, 0xc6, 0x7a, 0x6a, 0x44, 0x99, 0xaa, 0x50,
    0x9b, 0xa0, 0xaf, 0x90, 0x27, 0x99, 0x2c, 0x86, 0x7b, 0xbe, 0xaa, 0x6d,
    0x7b, 0x6a, 0xa1, 0x97, 0x1e, 0x7b, 0x34, 0x26, 0x93, 0x09, 0x2b, 0xd3,
    0x15, 0x0e, 0xde, 0x73, 0x2f, 0xcd, 0xa4, 0xc5, 0xfa, 0x05, 0xc3, 0x99,
    0xd3, 0xa4, 0xe9, 0x04, 0xfd, 0xfe, 0x59, 0x7c, 0x65, 0xc2, 0xea, 0xed,
    0x77, 0xc0, 0xac, 0x41, 0xda, 0x4c, 0x48, 0x10, 0xed, 0xb8, 0xa8, 0x4b,
    0x02, 0x71, 0xa8, 0x85, 0xf0, 0x80, 0xec, 0x20, 0x8e, 0x25, 0x41, 0x27,
    0x09, 0xcb, 0x82, 0x37, 0x89, 0x10, 0xa1, 0xed, 0x83, 0xec, 0xc1, 0xb4,
    0x59, 0x61, 0x9a, 0x85, 0x64, 0xe0, 0x55, 0x19, 0xdc, 0x78, 0xfc, 0x89,
    0x87, 0x77, 0xd4, 0x5d, 0x7b, 0x12, 0x58, 0x9d, 0x65, 0x26, 0x6d, 0x22,
    0xaf, 0xaf, 0xb0, 0x72, 0xdb, 0xcd, 0x10, 0x4e, 0x59, 0x5c, 0x24, 0x4d,
    0x26, 0x6c, 0x9e, 0x7c, 0x09, 0x31, 0x63, 0x36, 0x3d, 0x40, 0xf5, 0x81,
    0x5a, 0x3a, 0x70, 0xc7, 0x9b, 0x04, 0x09, 0x6a, 0x93, 0xc1, 0x14, 0xc7,
    0x71, 0x77, 0x3c, 0x1c, 0x4f, 0x09, 0x0f, 0xa8, 0x04, 0xea, 0x4e, 0x44,
    0xe0, 0xaa, 0x78, 0x28, 0x3e, 0x81, 0xa6, 0x99, 0x10, 0x59, 0x88, 0xa6,
    0x25, 0xe5, 0x84, 0x37, 0x10, 0x56, 0x59, 0x3d, 0xbb, 0xdc, 0x7f, 0x04,
    0xbe, 0xf1, 0xd8, 0x27, 0x23, 0xe5, 0x86, 0x3c, 0x6d, 0x59, 0xbf, 0xfb,
    0x1e, 0xa2, 0x11, 0xa2, 0x56, 0x52, 0xa7, 0x6c, 0x7f, 0xef, 0x15, 0x26,
    0x87, 0x0f, 0x13, 0x29, 0x53, 0x5c, 0xf1, 0xad, 0x2d, 0x22, 0x09, 0x38,
    0x63, 0x04, 0xdc, 0xa0, 0x16, 0x34, 0xc0, 0x6a, 0x25, 0x52, 0x60, 0x1e,
    0x78, 0xbc, 0xf6, 0x3f, 0x41, 0xe4, 0x40, 0x13, 0x94, 0x49, 0xa2, 0xa6,
    0x8c, 0x17, 0xd0, 0x70, 0xc4, 0x0d, 0x51, 0xa1, 0x49, 0x0e, 0x9e, 0xd0,
    0x50, 0x4c, 0xeb, 0x8e, 0x36, 0xee, 0x5a, 0x03, 0xb3, 0xb6, 0xa1, 0x9d,
    0xb5, 0x48, 0x16, 0x62, 0x6d, 0x85, 0xba, 0xbd, 0x0d, 0x2e, 0x0c, 0x8b,
    0x6d, 0xda, 0xa6, 0x65, 0x71, 0xfa, 0x34, 0xa4, 0x44, 0xd4, 0x82, 0x7b,
    0x10, 0x29, 0x88, 0x08, 0x44, 0x6d, 0xf4, 0xa8, 0x2b, 0x98, 0x12, 0x59,
    0xa8, 0x16, 0x88, 0x08, 0x8e, 0x43, 0x93, 0xb0, 0x70, 0x6c, 0xe0, 0xf2,
    0x80, 0xc3, 0x1d, 0x9f, 0x40, 0xa4, 0x40, 0x1d, 0xd2, 0x0c, 0xea, 0x90,
    0x91, 0x89, 0x52, 0xba, 0x86, 0xd4, 0xec, 0xac, 0xdc, 0x77, 0x25, 0xd0,
    0xcc, 0x12, 0x39, 0x02, 0x69, 0x5a, 0x26, 0x93, 0x19, 0xbe, 0x5c, 0xb2,
    0xd8, 0xb8, 0x48, 0x4c, 0x32, 0x83, 0x16, 0x5c, 0x15, 0x70, 0xa2, 0xcd,
    0x78, 0xe7, 0x88, 0x1a, 0xda, 0x38, 0x82, 0x13, 0xd5, 0x50, 0x77, 0x0c,
    0xa3, 0x5a, 0x1d, 0x87, 0xa2, 0x38, 0xe6, 0x41, 0x2d, 0x95, 0x10, 0x48,
    0xe1, 0x2c, 0x45, 0xa8, 0x38, 0x61, 0x81, 0x27, 0x30, 0x11, 0xa4, 0x15,
    0x6c, 0x6b, 0x20, 0x85, 0x63, 0xe6, 0x20, 0x41, 0xc4, 0xce, 0x9d, 0x74,
    0x57, 0x02, 0x62, 0x81, 0xb5, 0x42, 0x98, 0x8d, 0xed, 0xcf, 0x1d, 0xf5,
    0x81, 0x58, 0x18, 0x11, 0x06, 0x61, 0x78, 0xdb, 0x90, 0xfb, 0x8a, 0x79,
    0x21, 0x99, 0xa2, 0x02, 0xc9, 0x0d, 0xc5, 0xa9, 0x04, 0x1e, 0x8e, 0x89,
    0xe0, 0xe2, 0x38, 0x60, 0x61, 0x58, 0x12, 0xcc, 0x15, 0xcb, 0x09, 0xca,
    0x12, 0xcf, 0xc2, 0xb0, 0x2a, 0x0c, 0x25, 0x20, 0x0a, 0xd1, 0x2b, 0x86,
    0x20, 0x6d, 0xe0, 0x25, 0x91, 0x72, 0x50, 0xcb, 0x55, 0x9c, 0xbc, 0x1b,
    0x81, 0xc8, 0x82, 0x34, 0x82, 0xb4, 0x19, 0x2b, 0x1d, 0x06, 0x60, 0x41,
    0x84, 0x11, 0x8b, 0xc5, 0x98, 0xcf, 0xee, 0x84, 0x19, 0x6e, 0x4a, 0xb5,
    0x8a, 0x85, 0x91, 0x04, 0x34, 0xc0, 0x55, 0x31, 0xc6, 0xe7, 0x11, 0x70,
    0x73, 0xcc, 0x82, 0x48, 0x86, 0x56, 0xf0, 0x64, 0x94, 0x59, 0xc2, 0x07,
    0xc3, 0x01, 0x42, 0xf1, 0x9c, 0xa8, 0xe6, 0x2c, 0x8b, 0x52, 0x44, 0xd1,
    0x70, 0x4c, 0x9d, 0xe5, 0xcd, 0x87, 0xf6, 0x4f, 0x40, 0x55, 0x29, 0xe2,
    0x68, 0x93, 0x98, 0x6f, 0x5d, 0x60, 0xb2, 0xba, 0x46, 0x16, 0xc3, 0xba,
    0x61, 0xcc, 0x59, 0x57, 0xc2, 0x2a, 0x39, 0x09, 0xc5, 0x1c, 0x55, 0x23,
    0x47, 0xc5, 0x12, 0xb8, 0x19, 0x78, 0x21, 0x18, 0x53, 0xc7, 0x03, 0x3c,
    0x39, 0x24, 0xc7, 0x05, 0x04, 0x1b, 0x23, 0x24, 0x89, 0x68, 0xc6, 0xb5,
    0x7c, 0x9a, 0x18, 0x4a, 0xa5, 0xeb, 0x95, 0x3c, 0x09, 0x6c, 0xdb, 0x48,
    0xab, 0x81, 0x57, 0xd0, 0xb8, 0x8e, 0x1a, 0xb0, 0x36, 0x63, 0x66, 0xd4,
    0x3a, 0xd0, 0x2f, 0xe6, 0xb4, 0x29, 0x33, 0x48, 0xe0, 0xb5, 0x10, 0x5a,
    0x11, 0xaf, 0x40, 0x42, 0x25, 0xc0, 0x1d, 0x89, 0x32, 0x7a, 0x58, 0xed,
    0xb5, 0x62, 0x05, 0xab, 0xe3, 0x54, 0x76, 0x33, 0xd4, 0x95, 0x92, 0x40,
    0xf5, 0x52, 0x7a, 0x29, 0xaa, 0x60, 0x56, 0x01, 0xa1, 0x5a, 0x45, 0xd5,
    0x29, 0x39, 0xd1, 0x55, 0x23, 0x26, 0x41, 0xb7, 0x14, 0x72, 0x1b, 0x3c,
    0xfa, 0x07, 0xd7, 0x31, 0x89, 0xab, 0x19, 0x43, 0xad, 0xb4, 0xa6, 0xe4,
    0x6e, 0xce, 0xa2, 0x49, 0xb4, 0x59, 0xb0, 0x30, 0x8a, 0x17, 0x32, 0x42,
    0xd6, 0x02, 0x29, 0x8d, 0x06, 0xbf, 0x26, 0x21, 0x22, 0x7c, 0x6c, 0xa3,
    0xe6, 0x44, 0x12, 0xcc, 0x8d, 0xc0, 0xa8, 0x1e, 0xd4, 0xaa, 0x04, 0x81,
    0x8a, 0x5f, 0x1e, 0x72, 0x21, 0x81, 0x5a, 0xa5, 0x24, 0x18, 0xb4, 0x60,
    0x38, 0x64, 0xd0, 0x92, 0xc8, 0x8d, 0x62, 0x76, 0xf5, 0x49, 0xbc, 0x2b,
    0x81, 0xa5, 0x3b, 0x0d, 0x4e, 0x2e, 0x15, 0xa9, 0x0a, 0x7d, 0x4f, 0x15,
    0x21, 0x5b, 0x45, 0xab, 0x82, 0x2b, 0x3e, 0x69, 0x21, 0x12, 0xe2, 0xc6,
    0xb8, 0x63, 0x01, 0xc1, 0x51, 0x7c, 0x14, 0x74, 0xe1, 0xa8, 0x39, 0xd5,
    0x0c, 0x8b, 0xb1, 0x90, 0x55, 0x8d, 0x88, 0x4a, 0xf5, 0xc0, 0x51, 0x34,
    0x67, 0xba, 0xce, 0x28, 0xaa, 0x78, 0x32, 0xbc, 0xab, 0x74, 0x65, 0x8c,
    0xa2, 0x6a, 0x22, 0xaf, 0x4e, 0xaf, 0x6a, 0xe3, 0xae, 0x83, 0xec, 0xfe,
    0x8f, 0x7e, 0x42, 0x7a, 0x73, 0x82, 0xca, 0x30, 0x2c, 0x58, 0x2e, 0xb7,
    0xe8, 0x4a, 0xc7, 0x42, 0x07, 0x3c, 0x0a, 0x2a, 0x8e, 0x59, 0x45, 0xb5,
    0xa0, 0x5a, 0x30, 0xaf, 0x84, 0x18, 0x16, 0x36, 0x0a, 0x3a, 0xf1, 0x51,
    0xc0, 0x61, 0xa3, 0xa8, 0x33, 0x43, 0xa4, 0x62, 0x66, 0x14, 0x49, 0x78,
    0x75, 0xaa, 0x1a, 0x43, 0xed, 0x18, 0xca, 0x40, 0xdf, 0x29, 0xdb, 0x7d,
    0xa5, 0x4a, 0x45, 0xcd, 0x89, 0x2c, 0xa4, 0x06, 0x7e, 0xf7, 0xd3, 0x5f,
    0xba, 0xaa, 0x1a, 0xdd, 0x53, 0xcc, 0x19, 0x46, 0xa7, 0x95, 0x56, 0xd2,
    0x28, 0x0b, 0xda, 0x42, 0x13, 0x4e, 0x95, 0xc4, 0xb4, 0x09, 0xaa, 0x35,
    0xe4, 0x14, 0x90, 0x1b, 0x1a, 0x37, 0xaa, 0x1a, 0xc1, 0x98, 0x66, 0x56,
    0xc7, 0xda, 0x88, 0x30, 0x0c, 0xc3, 0x45, 0xd0, 0x30, 0x98, 0x08, 0x51,
    0x2a, 0x7d, 0x38, 0xea, 0xc6, 0x7c, 0xee, 0x14, 0x81, 0xda, 0x1a, 0x2e,
    0x0d, 0x56, 0x0b, 0x55, 0x8d, 0x44, 0x62, 0x75, 0xe5, 0xea, 0xde, 0xdf,
    0x33, 0x02, 0x00, 0xef, 0x7d, 0xe8, 0x8f, 0x44, 0x5d, 0xb1, 0xd2, 0xd1,
    0x0d, 0x1d, 0x7d, 0xe9, 0xe9, 0xbd, 0xe0, 0x3e, 0x2e, 0xa2, 0x56, 0x50,
    0x57, 0xbc, 0xf4, 0x97, 0xdb, 0xa8, 0x7b, 0x3f, 0xfe, 0x26, 0x67, 0xe1,
    0xc1, 0x10, 0xc1, 0xe0, 0xc6, 0xe0, 0x95, 0x41, 0x2b, 0x5d, 0x3f, 0xd0,
    0x9b, 0x33, 0x78, 0x65, 0xab, 0x77, 0xb4, 0x55, 0x8a, 0x3a, 0x96, 0x33,
    0xa6, 0x46, 0x67, 0x99, 0x10, 0x41, 0x72, 0xf0, 0xd0, 0x2e, 0x7b, 0x81,
    0x6b, 0x8a, 0x00, 0xc0, 0x42, 0x03, 0x93, 0x4a, 0x76, 0x41, 0x0d, 0xa6,
    0xb3, 0x8c, 0xa5, 0xb8, 0xac, 0x5b, 0x9a, 0xa6, 0xc1, 0x92, 0x80, 0x3b,
    0xad, 0x04, 0x26, 0x31, 0x6a, 0x20, 0x7f, 0x4d, 0xff, 0x78, 0x61, 0xb0,
    0x31, 0x3a, 0x35, 0x84, 0x65, 0x0d, 0xdc, 0x0a, 0x43, 0x31, 0x3c, 0x3b,
    0xae, 0xa3, 0x00, 0xac, 0x5a, 0x50, 0x1c, 0x2d, 0x85, 0xb6, 0x15, 0x54,
    0xf6, 0x3e, 0xf9, 0xbc, 0xa6, 0xb3, 0xd1, 0xfb, 0x3f, 0xf2, 0x09, 0x59,
    0x58, 0x50, 0x12, 0x74, 0x3e, 0xb0, 0x18, 0x06, 0x16, 0x65, 0xf4, 0xe6,
    0x20, 0xc1, 0x56, 0x29, 0xf4, 0x43, 0xa1, 0x2f, 0x85, 0x2d, 0x73, 0x16,
    0xb5, 0xb2, 0x2c, 0xca, 0xe0, 0x95, 0x5e, 0x94, 0xad, 0x5e, 0x19, 0xd4,
    0x18, 0x96, 0x03, 0xfd, 0x50, 0xf0, 0x5a, 0xc6, 0xbd, 0xc1, 0x04, 0xb4,
    0x3a, 0x7d, 0x02, 0x4f, 0x4a, 0x55, 0xc3, 0x8a, 0x21, 0x92, 0x51, 0x09,
    0xfe, 0xe5, 0x3b, 0x67, 0x39, 0x76, 0xec, 0xd8, 0xae, 0x67, 0xb0, 0xd7,
    0xb4, 0x23, 0xbb, 0x84, 0xbf, 0xff, 0xdc, 0xc7, 0x62, 0xb6, 0x36, 0x21,
    0x7b, 0x40, 0x82, 0x36, 0x84, 0xd4, 0x36, 0x64, 0x0f, 0x2c, 0x09, 0x82,
    0xa1, 0xe1, 0x64, 0x09, 0x34, 0x37, 0xf8, 0xa0, 0x98, 0x08, 0xa6, 0x95,
    0xa1, 0x1f, 0xbb, 0x4a, 0x4a, 0xca, 0x96, 0x25, 0x92, 0x3a, 0x4a, 0xa2,
    0xe6, 0x40, 0x2b, 0x54, 0xed, 0xd8, 0xec, 0x83, 0x65, 0x5f, 0xc8, 0x54,
    0x4e, 0xfe, 0xdf, 0x36, 0xdf, 0x7c, 0xf9, 0xdc, 0x15, 0xeb, 0xef, 0x74,
    0xd2, 0xb7, 0x2f, 0x02, 0x00, 0x5f, 0x7f, 0xe2, 0xf7, 0xa3, 0x49, 0x01,
    0x15, 0x9a, 0x49, 0x22, 0x34, 0x90, 0xa9, 0x90, 0xdc, 0x49, 0x29, 0xa1,
    0x01, 0x65, 0x70, 0xdc, 0x14, 0x92, 0x53, 0x2d, 0xa0, 0x81, 0xa1, 0x08,
    0x39, 0x0d, 0x84, 0x05, 0xc5, 0x41, 0x9b, 0x44, 0x1b, 0x79, 0x94, 0xd3,
    0x14, 0x16, 0x25, 0xe8, 0x37, 0xc7, 0x3a, 0x3a, 0xb7, 0x2c, 0xfc, 0xd3,
    0x8b, 0xa7, 0x76, 0x5c, 0xff, 0x8d, 0x24, 0xf6, 0x7d, 0xc1, 0xf1, 0x4b,
    0x0f, 0x3f, 0x26, 0x17, 0xb6, 0x3a, 0x4a, 0x52, 0xe6, 0xae, 0x2c, 0x43,
    0x59, 0xf6, 0x3d, 0xf3, 0x52, 0xd8, 0x5a, 0xf4, 0x6c, 0x2f, 0x3a, 0x96,
    0xc3, 0x92, 0x85, 0x0e, 0x6c, 0x57, 0xa5, 0x2b, 0x03, 0xf3, 0x65, 0x4f,
    0xf5, 0x05, 0x5d, 0x16, 0x4a, 0x72, 0x6c, 0x92, 0x71, 0x77, 0x96, 0xa6,
    0xf4, 0x55, 0xe9, 0x96, 0x86, 0xd5, 0x81, 0x48, 0xc6, 0xb6, 0xda, 0x55,
    0x8d, 0xdf, 0x09, 0xd7, 0x7c, 0xc1, 0x71, 0x09, 0xc7, 0x8e, 0x1d, 0x8b,
    0xd5, 0xb5, 0x29, 0xef, 0xfb, 0x85, 0x7b, 0xb8, 0xe5, 0xc8, 0x0a, 0xd1,
    0x66, 0x6a, 0x09, 0x24, 0x1c, 0x0b, 0x48, 0x28, 0xa5, 0x82, 0x87, 0x8e,
    0x5b, 0xc9, 0x94, 0xc0, 0x95, 0x14, 0x09, 0x9d, 0x07, 0x59, 0x32, 0x32,
    0x31, 0x8c, 0x71, 0x6f, 0x30, 0xce, 0x01, 0x23, 0x22, 0xd8, 0xea, 0x9d,
    0xaf, 0xbf, 0xf0, 0xbf, 0xfb, 0xb2, 0x67, 0xdf, 0x29, 0x74, 0x89, 0x04,
    0xc0, 0xfd, 0x3f, 0x77, 0x27, 0xef, 0xb9, 0xeb, 0xc6, 0x71, 0xab, 0x08,
    0xe4, 0x36, 0xa8, 0x9d, 0x11, 0x12, 0xe4, 0x2c, 0x04, 0x46, 0xca, 0x0d,
    0x45, 0x61, 0x96, 0xc6, 0xd3, 0x09, 0xbf, 0xf4, 0x91, 0x69, 0x83, 0x57,
    0xa7, 0x57, 0xa7, 0x14, 0xe5, 0xe5, 0xf3, 0x73, 0x9e, 0xff, 0xe6, 0xee,
    0x9e, 0xdf, 0xa9, 0x06, 0xf6, 0x1d, 0x81, 0xd7, 0xe3, 0x9f, 0x5f, 0xfa,
    0x2e, 0xff, 0x7e, 0xea, 0x2c, 0xc7, 0xde, 0x79, 0x2b, 0xef, 0xbc, 0x69,
    0x8d, 0x5a, 0x82, 0x12, 0x70, 0x7e, 0xbe, 0xe4, 0x1f, 0xfe, 0xe3, 0x34,
    0x1b, 0xaf, 0x1d, 0xf2, 0xae, 0x1f, 0x3e, 0xc0, 0x7d, 0x3f, 0x75, 0x94,
    0x9b, 0x0e, 0x4e, 0x59, 0x9d, 0xb6, 0xcc, 0x9a, 0x00, 0x9c, 0xce, 0x9d,
    0x57, 0xcf, 0x2c, 0xf9, 0xc6, 0xa9, 0xf3, 0x6c, 0x6e, 0x2c, 0xf6, 0x65,
    0xf8, 0x25, 0x5c, 0x57, 0x04, 0x2e, 0xe1, 0x8d, 0x2d, 0xee, 0xb6, 0x3b,
    0x8e, 0x22, 0xc0, 0xab, 0xaf, 0x9c, 0xbf, 0xee, 0x6f, 0xbe, 0x1e, 0xd7,
    0x72, 0xbf, 0xf0, 0x23, 0x11, 0x78, 0x3d, 0xf6, 0xea, 0xd7, 0xfb, 0xc1,
    0x7e, 0x2e, 0x46, 0x7e, 0x6c, 0x04, 0xde, 0x2a, 0xfc, 0xc4, 0xdf, 0x13,
    0xbf, 0x4d, 0xe0, 0xad, 0xc6, 0xff, 0x03, 0xe7, 0x45, 0x80, 0x84, 0x7a,
    0x0a, 0x51, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae,
    0x42, 0x60, 0x82
  };

  static QImage img;
  img.loadFromData( apple_data, sizeof( apple_data ) );
  
  return ( &img );
}
