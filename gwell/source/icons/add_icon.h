#include "icons.h"


const QImage* Icons::addIcon()
{
  const unsigned char add_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x77, 0x3d, 0xf8, 0x00, 0x00, 0x01,
    0x33, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x95, 0x2f, 0x4f, 0xc3,
    0x50, 0x14, 0x47, 0x4f, 0xc9, 0xe0, 0x43, 0x61, 0x11, 0x48, 0x44, 0x67,
    0xd1, 0x24, 0x28, 0x04, 0x02, 0x8f, 0x20, 0x08, 0x92, 0x29, 0x1c, 0x8a,
    0x20, 0x48, 0xd8, 0xd7, 0x98, 0x9c, 0x40, 0x20, 0x31, 0x7c, 0x82, 0xad,
    0xe9, 0xfb, 0x73, 0xdf, 0x7d, 0x1d, 0x02, 0xba, 0xb4, 0x4b, 0x5b, 0xca,
    0xd8, 0x0c, 0xd9, 0x75, 0x6d, 0x6e, 0x7f, 0xe7, 0xf5, 0xf4, 0xbe, 0xd7,
    0x64, 0x32, 0x99, 0xb0, 0xcd, 0xda, 0xdb, 0x6a, 0xfa, 0x0e, 0xd0, 0xa7,
    0x06, 0x7d, 0x9a, 0xd2, 0x74, 0xb8, 0x68, 0xba, 0x3f, 0x1e, 0xbf, 0x24,
    0x1b, 0x01, 0x00, 0x5c, 0x3e, 0x5f, 0x01, 0x60, 0xc4, 0x01, 0x70, 0x7f,
    0x3a, 0xea, 0xf5, 0x5c, 0x6f, 0x40, 0x19, 0x0c, 0x60, 0xbd, 0xeb, 0xe8,
    0x5c, 0x13, 0x00, 0x10, 0x54, 0xd1, 0xa8, 0x35, 0xd8, 0x5a, 0x80, 0x26,
    0xe7, 0x41, 0x15, 0x23, 0x16, 0xd1, 0x40, 0x88, 0xda, 0xd8, 0xd7, 0xf4,
    0x4d, 0x5a, 0xdf, 0xe0, 0xfc, 0xf1, 0x82, 0x83, 0xc1, 0x3e, 0xa2, 0x01,
    0xeb, 0x1d, 0x46, 0x2c, 0x1a, 0x23, 0x21, 0x2a, 0x99, 0xcd, 0x39, 0xba,
    0x3d, 0xc1, 0x8a, 0x43, 0x34, 0x60, 0xc4, 0xf1, 0x76, 0xd3, 0x7c, 0x22,
    0x74, 0x2a, 0xca, 0x9d, 0x5d, 0x2a, 0xf1, 0x2a, 0xc4, 0x22, 0x62, 0xbc,
    0x43, 0x8b, 0x48, 0xd0, 0x80, 0x15, 0x8f, 0x57, 0xc1, 0x75, 0x28, 0x6b,
    0x05, 0x94, 0x4a, 0x34, 0xc6, 0xaf, 0x90, 0x20, 0x04, 0x0d, 0x68, 0x11,
    0xc9, 0x9d, 0x21, 0x16, 0x05, 0x33, 0x33, 0x07, 0x20, 0x73, 0xf9, 0xef,
    0x01, 0x55, 0xdf, 0x65, 0x78, 0x55, 0x49, 0xb9, 0xea, 0xcc, 0xe5, 0x98,
    0x8e, 0xa9, 0x6a, 0x05, 0x3c, 0x9d, 0x3d, 0xd4, 0xae, 0x0f, 0xaf, 0x8f,
    0x6b, 0x4a, 0xde, 0xef, 0xa6, 0xad, 0xa1, 0x3f, 0x02, 0x56, 0xa7, 0x21,
    0x4d, 0x87, 0x0b, 0x2b, 0x7e, 0xa9, 0xa4, 0x1c, 0xd3, 0x8d, 0xee, 0xe4,
    0x99, 0x99, 0x7f, 0xeb, 0xf2, 0x9d, 0x4a, 0x56, 0xab, 0xf7, 0x61, 0x57,
    0x0d, 0xb7, 0x7f, 0xdd, 0x68, 0x4d, 0xf5, 0x31, 0x7a, 0xed, 0x1d, 0x5a,
    0xad, 0x64, 0xf7, 0xcb, 0xfc, 0xff, 0x80, 0x4f, 0x00, 0xd3, 0xe4, 0xcd,
    0x2d, 0xcf, 0x8b, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
    0xae, 0x42, 0x60, 0x82
  };

  static QImage img;
  img.loadFromData( add_data, sizeof( add_data ) );
  
  return ( &img );
}

