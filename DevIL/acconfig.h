#ifndef __CONFIG_H__
#define __CONFIG_H__
@TOP@

/*
 __BIG_ENDIAN__ src/il_convert.c src/il_endian.c
__BORLANDC__ src/il_tiff.c
DJGPP src/il_png.c src/il_targa.c
*/

/* Supported images formats (il) */

#undef IL_NO_BMP
#undef IL_NO_DCX
#undef IL_NO_DDS
#undef IL_NO_DOOM
#undef IL_NO_GIF
#undef IL_NO_ICO
#undef IL_NO_JPG
#undef IL_NO_LCMS
#undef IL_NO_LIF
#undef IL_NO_MDL
#undef IL_NO_MNG
#undef IL_NO_PCD
#undef IL_NO_PCX
#undef IL_NO_PIC
#undef IL_NO_PNG
#undef IL_NO_PNM
#undef IL_NO_RAW
#undef IL_NO_SGI
#undef IL_NO_TGA
#undef IL_NO_TIF
#undef IL_NO_WAL

/* Supported api (ilut) */

#undef ILUT_USE_ALLEGRO
#undef ILUT_USE_DIRECTX8
#undef ILUT_USE_OPENGL
#undef ILUT_USE_SDL
#undef ILUT_USE_WIN32

/* CPU type */

#undef WORDS_BIGENDIAN

/*
__LITTLE_ENDIAN__ src/il_endian.c src/il_png.c src/il_sgi.c src/il_tiff.c
_MEM_DEBUG src/il_istack.c
_MSC_VER src/il_cut.c
RGB_RED src/il_jpeg.c
_WIN32 src/il_internal.c src/il_main.c src/il_png.c src/il_profiles.c src/il_targa.c src/il_tiff.c
_WIN32_WCE src/il_files.c src/il_header.c src/il_internal.c src/il_io.c src/il_main.c src/il_pal.c src/il_register.c
*/

@BOTTOM@
#endif /* __CONFIG_H__ */