//-----------------------------------------------------------------------------
//
// ImageLib Sources
// Copyright (C) 2000-2001 by Denton Woods
// Last modified: 12/04/2001 <--Y2K Compliant! =]
//
// Filename: openil/internal.h
//
// Description: Internal stuff for DevIL
//
//-----------------------------------------------------------------------------

#ifndef INTERNAL_H
#define INTERNAL_H


#define _IL_BUILD_LIBRARY

// Standard headers
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Local headers
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <IL/il.h>

#include "il_files.h"
#include "il_error.h"
#include "il_endian.h"
#include "il_alloc.h"

// Windows-specific
#ifdef _WIN32
	#ifdef _MSC_VER
		#if _MSC_VER > 1000
			#pragma once
			#pragma intrinsic(memcpy)
			#pragma intrinsic(memset)
			#pragma intrinsic(strcmp)
			#pragma intrinsic(strlen)
			#pragma intrinsic(strcpy)
			#if _MSC_VER >= 1300  // Erroneous size_t conversion warnings
				#pragma warning(disable : 4267)
			#endif
			#pragma comment(linker, "/NODEFAULTLIB:libc")
			#pragma comment(linker, "/NODEFAULTLIB:libcd")
			#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
			#ifdef _DEBUG
				#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
			#endif // _DEBUG
		#endif // _MSC_VER > 1000
	#endif
	#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
#endif


// Windows has a TEXT macro defined in WinNT.h that makes string Unicode if UNICODE is defined.
/*#ifndef _WIN32
	#define IL_TEXT(s) s
#endif*/

/*#ifdef _WIN32_WCE
	#define IL_TEXT(s) ((char*)TEXT(s))
#elif _WIN32
	#define IL_TEXT(s) (s)
#else
	#define IL_TEXT(s) (s)
	#define TEXT(s) (s)
#endif*/

#ifdef _UNICODE
	#define IL_TEXT(s) L##s
#else
	#define IL_TEXT(s) (s)
#endif

#ifdef IL_INLINE_ASM
	#ifdef _WIN32
		#define USE_WIN32_ASM
	#endif
#endif


#define IL_MAX(a,b) (((a) > (b)) ? (a) : (b))


// Basic Palette struct
typedef struct ILpal
{
	ILubyte	*Palette;		// the image palette (if any)
	ILuint	PalSize;		// size of the palette (in bytes)
	ILenum	PalType;		// the palette types below (0x0500 range)
} ILpal;


// The Fundamental Image struct
typedef struct ILimage
{
	ILuint	Width;				// the image's width
	ILuint	Height;				// the image's height
	ILuint	Depth;				// the image's depth
	ILubyte	Bpp;				// bytes per pixel (now number of channels)
	ILubyte	Bpc;				// bytes per channel
	ILuint	Bps;				// bytes per scanline (components for IL)
	ILubyte	*Data;				// the image data
	ILuint	SizeOfData;			// the total size of the data (in bytes)
	ILuint	SizeOfPlane;		// SizeOfData in a 2d image, size of each plane slice in a 3d image (in bytes)
	ILenum	Format;				// image format (in IL enum style)
	ILenum	Type;				// image type (in IL enum style)
	ILenum	Origin;				// origin of the image
	ILpal	Pal;				// palette details
	ILuint	Duration;			// length of the time to display this "frame"
	struct	ILimage *Mipmaps;	// mipmapped versions of this image terminated by a NULL - usu. NULL
	struct	ILimage *Next;		// next image in the chain - usu. NULL
	struct	ILimage *Layers;	// subsequent layers in the chain - usu. NULL
	ILuint	NumNext;			// number of images following this one (0 when not parent)
	ILuint	NumMips;			// number of mipmaps (0 when not parent)
	ILuint	NumLayers;			// number of layers (0 when not parent)
	ILuint	*AnimList;			// animation list
	ILuint	AnimSize;			// animation list size
	ILvoid	*Profile;			// colour profile
	ILuint	ProfileSize;		// colour profile size
	ILuint	OffX, OffY;			// offset of the image
} ILimage;


extern ILimage *iCurImage;


#define BIT_0	1
#define BIT_1	2
#define BIT_2	4
#define BIT_3	8
#define BIT_4	16
#define BIT_5	32
#define BIT_6	64
#define BIT_7	128
#define BIT_8	256
#define BIT_9	512
#define BIT_10	1024
#define BIT_11	2048
#define BIT_12	4096
#define BIT_13	8192
#define BIT_14	16384
#define BIT_15	32768
#define BIT_16	65536
#define BIT_17	131072
#define BIT_18	262144
#define BIT_19	524288
#define BIT_20	1048576
#define BIT_21	2097152
#define BIT_22	4194304
#define BIT_23	8388608
#define BIT_24	16777216
#define BIT_25	33554432
#define BIT_26	67108864
#define BIT_27	134217728
#define BIT_28	268435456
#define BIT_29	536870912
#define BIT_30	1073741824
#define BIT_31	2147483648
#define BIT_32	4294967296

#define NUL '\0'  // Easier to type and ?portable?


#if !_WIN32 || _WIN32_WCE
	int stricmp(const char *src1, const char *src2);
	int strnicmp(const char *src1, const char *src2, size_t max);
#endif//_WIN32

int iStrCmp(const ILstring src1, const ILstring src2);


//
// Useful miscellaneous functions
//

ILboolean	iCheckExtension(const ILstring Arg, const ILstring Ext);
ILbyte*		iFgets(char *buffer, ILuint maxlen);
ILboolean	iFileExists(const ILstring FileName);
ILstring	iGetExtension(const ILstring FileName);
char*		ilStrDup(const char *Str);
ILuint		ilStrLen(const char *Str);


// Miscellaneous functions
ILvoid					ilDefaultStates(ILvoid);
ILenum					iGetHint(ILenum Target);
ILint					iGetInt(ILenum Mode);
ILvoid					ilRemoveRegistered(ILvoid);
ILAPI ILvoid ILAPIENTRY	ilSetCurImage(ILimage *Image);


//
// Rle compression
//
#define		IL_TGACOMP 0x01
#define		IL_PCXCOMP 0x02
#define		IL_SGICOMP 0x03
ILboolean	ilRleCompressLine(ILubyte *ScanLine, ILuint Width, ILubyte Bpp, ILubyte *Dest, ILuint *DestWidth, ILenum CompressMode);
ILuint		ilRleCompress(ILubyte *Data, ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILubyte *Dest, ILenum CompressMode, ILuint *ScanTable);


//
// Utility functions
//
ILAPI ILubyte	ILAPIENTRY ilGetBppFormat(ILenum Format);
ILAPI ILubyte	ILAPIENTRY ilGetBppPal(ILenum PalType);
ILAPI ILubyte	ILAPIENTRY ilGetBppType(ILenum Type);
ILAPI ILenum	ILAPIENTRY ilGetTypeBpc(ILubyte Bpc);
ILAPI ILenum	ILAPIENTRY ilGetPalBaseType(ILenum PalType);
ILAPI ILuint	ILAPIENTRY ilNextPower2(ILuint Num);
ILAPI ILenum	ILAPIENTRY ilTypeFromExt(const ILstring FileName);


//
// Image functions
//
ILAPI ILvoid	ILAPIENTRY	iBindImageTemp(ILvoid);
ILAPI ILboolean ILAPIENTRY	ilClearImage_(ILimage *Image);
ILAPI ILvoid	ILAPIENTRY	ilCloseImage(ILimage *Image);
ILAPI ILvoid	ILAPIENTRY	ilClosePal(ILpal *Palette);
ILAPI ILpal*	ILAPIENTRY	iCopyPal(ILvoid);
ILAPI ILboolean	ILAPIENTRY	ilCopyImageAttr(ILimage *Dest, ILimage *Src);
ILAPI ILimage*	ILAPIENTRY	ilCopyImage_(ILimage *Src);
ILAPI ILvoid	ILAPIENTRY	ilGetClear(ILvoid *Colours, ILenum Format, ILenum Type);
ILAPI ILuint	ILAPIENTRY	ilGetCurName(ILvoid);
ILAPI ILboolean	ILAPIENTRY	ilIsValidPal(ILpal *Palette);
ILAPI ILimage*	ILAPIENTRY	ilNewImage(ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILubyte Bpc);
ILAPI ILboolean ILAPIENTRY	ilResizeImage(ILimage *Image, ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILubyte Bpc);
ILvoid						iSetImage0(ILvoid);
ILAPI ILboolean ILAPIENTRY	ilTexImage_(ILimage *Image, ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILenum Format, ILenum Type, ILvoid *Data);
ILAPI ILboolean ILAPIENTRY	ilTexSubImage_(ILimage *Image, ILvoid *Data);


// Conversion functions
ILboolean					ilAddAlpha(ILvoid);
ILboolean					ilAddAlphaKey(ILimage *Image);
ILAPI ILvoid*	ILAPIENTRY	ilConvertBuffer(ILuint SizeOfData, ILenum SrcFormat, ILenum DestFormat, ILenum SrcType, ILenum DestType, ILvoid *Buffer);
ILAPI ILimage*	ILAPIENTRY	iConvertImage(ILenum DestFormat, ILenum DestType);
ILboolean					iFastConvert(ILenum DestFormat);
ILAPI ILpal*	ILAPIENTRY	iConvertPal(ILpal *Pal, ILenum DestFormat);
ILboolean					ilFixImage(ILvoid);
ILAPI ILubyte*	ILAPIENTRY	iGetFlipped(ILimage *Image);
ILboolean					ilRemoveAlpha(ILvoid);
ILboolean					ilSwapColours(ILvoid);


// Miscellaneous functions
char *iGetString(ILenum StringName);  // Internal version of ilGetString



// Library usage
#if _MSC_VER && !_WIN32_WCE
	#ifndef IL_NO_GIF
		#ifndef IL_DEBUG
			#pragma comment(lib, "libungif.lib")
		#else
			#pragma comment(lib, "debug/libungif.lib")
		#endif
	#endif
	#ifndef IL_NO_JPG
		#ifdef IL_USE_IJL
			#pragma comment(lib, "ijl15.lib")
		#else
			#ifndef IL_DEBUG
				#pragma comment(lib, "libjpeg.lib")
			#else
				#pragma comment(lib, "debug/libjpeg.lib")
			#endif
		#endif
	#endif
	#ifndef IL_NO_MNG
		#ifndef IL_DEBUG
			#pragma comment(lib, "libmng.lib")
			#pragma comment(lib, "libjpeg.lib")  // For JNG support.
		#else
			#pragma comment(lib, "debug/libmng.lib")
			#pragma comment(lib, "debug/libjpeg.lib")  // For JNG support.
		#endif
	#endif
	#ifndef IL_NO_PNG
		#ifndef IL_DEBUG
			#pragma comment(lib, "libpng.lib")
		#else
			#pragma comment(lib, "debug/libpng.lib")
		#endif
	#endif
	#ifndef IL_NO_TIF
		#ifndef IL_DEBUG
			#pragma comment(lib, "libtiff.lib")
		#else
			#pragma comment(lib, "debug/libtiff.lib")
		#endif
	#endif

	#if !defined(IL_NO_MNG) || !defined(IL_NO_PNG)
		#ifndef IL_DEBUG
			#pragma comment(lib, "zlib.lib")
		#else
			#pragma comment(lib, "debug/zlib.lib")
		#endif
	#endif
#endif


//
// Image loading/saving functions
//

ILboolean ilIsValidBmp(const ILstring FileName);
ILboolean ilIsValidBmpF(ILHANDLE File);
ILboolean ilIsValidBmpL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadBmp(const ILstring FileName);
ILboolean ilLoadBmpF(ILHANDLE File);
ILboolean ilLoadBmpL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveBmp(const ILstring FileName);
ILboolean ilSaveBmpF(ILHANDLE File);
ILboolean ilSaveBmpL(ILvoid *Lump, ILuint Size);

ILboolean ilSaveCHeader(const ILstring FileName, const char *InternalName);

ILboolean ilLoadCut(const ILstring FileName);
ILboolean ilLoadCutF(ILHANDLE File);
ILboolean ilLoadCutL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidDcx(const ILstring FileName);
ILboolean ilIsValidDcxF(ILHANDLE File);
ILboolean ilIsValidDcxL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadDcx(const ILstring FileName);
ILboolean ilLoadDcxF(ILHANDLE File);
ILboolean ilLoadDcxL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidDds(const ILstring FileName);
ILboolean ilIsValidDdsF(ILHANDLE File);
ILboolean ilIsValidDdsL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadDds(const ILstring FileName);
ILboolean ilLoadDdsF(ILHANDLE File);
ILboolean ilLoadDdsL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadDoom(const ILstring FileName);
ILboolean ilLoadDoomF(ILHANDLE File);
ILboolean ilLoadDoomL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadDoomFlat(const ILstring FileName);
ILboolean ilLoadDoomFlatF(ILHANDLE File);
ILboolean ilLoadDoomFlatL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidGif(const ILstring FileName);
ILboolean ilIsValidGifF(ILHANDLE File);
ILboolean ilIsValidGifL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadGif(const ILstring FileName);
ILboolean ilLoadGifF(ILHANDLE File);
ILboolean ilLoadGifL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadIcon(const ILstring FileName);
ILboolean ilLoadIconF(ILHANDLE File);
ILboolean ilLoadIconL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidJpg(const ILstring FileName);
ILboolean ilIsValidJpgF(ILHANDLE File);
ILboolean ilIsValidJpgL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadJpeg(const ILstring FileName);
ILboolean ilLoadJpegF(ILHANDLE File);
ILboolean ilLoadJpegL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveJpeg(const ILstring FileName);
ILboolean ilSaveJpegF(ILHANDLE File);
ILboolean ilSaveJpegL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadLbm(const ILstring FileName);
ILboolean ilLoadLbmF(ILHANDLE File);
ILboolean ilLoadLbmL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidLif(const ILstring FileName);
ILboolean ilIsValidLifF(ILHANDLE File);
ILboolean ilIsValidLifL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadLif(const ILstring FileName);
ILboolean ilLoadLifF(ILHANDLE File);
ILboolean ilLoadLifL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadMdl(const ILstring FileName);
ILboolean ilLoadMdlF(ILHANDLE File);
ILboolean ilLoadMdlL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidMng(const ILstring FileName);
ILboolean ilIsValidMngF(ILHANDLE File);
ILboolean ilIsValidMngL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadMng(const ILstring FileName);
ILboolean ilLoadMngF(ILHANDLE File);
ILboolean ilLoadMngL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveMng(const ILstring FileName);
ILboolean ilSaveMngF(ILHANDLE File);
ILboolean ilSaveMngL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadPcd(const ILstring FileName, ILuint PicNum);
ILboolean ilLoadPcdF(ILHANDLE File, ILuint PicNum);
ILboolean ilLoadPcdL(ILvoid *Lump, ILuint Size, ILuint PicNum);

ILboolean ilIsValidPcx(const ILstring FileName);
ILboolean ilIsValidPcxF(ILHANDLE File);
ILboolean ilIsValidPcxL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadPcx(const ILstring FileName);
ILboolean ilLoadPcxF(ILHANDLE File);
ILboolean ilLoadPcxL(ILvoid *Lump, ILuint Size);
ILboolean ilSavePcx(const ILstring FileName);
ILboolean ilSavePcxF(ILHANDLE File);
ILboolean ilSavePcxL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidPic(const ILstring FileName);
ILboolean ilIsValidPicF(ILHANDLE File);
ILboolean ilIsValidPicL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadPic(const ILstring FileName);
ILboolean ilLoadPicF(ILHANDLE File);
ILboolean ilLoadPicL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidPng(const ILstring FileName);
ILboolean ilIsValidPngF(ILHANDLE File);
ILboolean ilIsValidPngL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadPng(const ILstring FileName);
ILboolean ilLoadPngF(ILHANDLE File);
ILboolean ilLoadPngL(ILvoid *Lump, ILuint Size);
ILboolean ilSavePng(const ILstring FileName);
ILboolean ilSavePngF(ILHANDLE File);
ILboolean ilSavePngL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidPnm(const ILstring FileName);
ILboolean ilIsValidPnmF(ILHANDLE File);
ILboolean ilIsValidPnmL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadPnm(const ILstring FileName);
ILboolean ilLoadPnmF(ILHANDLE File);
ILboolean ilLoadPnmL(ILvoid *Lump, ILuint Size);
ILboolean ilSavePnm(const ILstring FileName);
ILboolean ilSavePnmF(ILHANDLE File);
ILboolean ilSavePnmL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidPsd(const ILstring FileName);
ILboolean ilIsValidPsdF(ILHANDLE File);
ILboolean ilIsValidPsdL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadPsd(const ILstring FileName);
ILboolean ilLoadPsdF(ILHANDLE File);
ILboolean ilLoadPsdL(ILvoid *Lump, ILuint Size);

ILboolean ilLoadRaw(const ILstring FileName);
ILboolean ilLoadRawF(ILHANDLE File);
ILboolean ilLoadRawL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveRaw(const ILstring FileName);
ILboolean ilSaveRawF(ILHANDLE File);
ILboolean ilSaveRawL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidSgi(const ILstring FileName);
ILboolean ilIsValidSgiF(ILHANDLE File);
ILboolean ilIsValidSgiL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadSgi(const ILstring FileName);
ILboolean ilLoadSgiF(ILHANDLE File);
ILboolean ilLoadSgiL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveSgi(const ILstring FileName);
ILboolean ilSaveSgiF(ILHANDLE File);
ILboolean ilSaveSgiL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidTga(const ILstring FileName);
ILboolean ilIsValidTgaF(ILHANDLE File);
ILboolean ilIsValidTgaL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadTarga(const ILstring FileName);
ILboolean ilLoadTargaF(ILHANDLE File);
ILboolean ilLoadTargaL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveTarga(const ILstring FileName);
ILboolean ilSaveTargaF(ILHANDLE File);
ILboolean ilSaveTargaL(ILvoid *Lump, ILuint Size);

ILboolean ilIsValidTiff(const ILstring FileName);
ILboolean ilIsValidTiffF(ILHANDLE File);
ILboolean ilIsValidTiffL(ILvoid *Lump, ILuint Size);
ILboolean ilLoadTiff(const ILstring FileName);
ILboolean ilLoadTiffF(ILHANDLE File);
ILboolean ilLoadTiffL(ILvoid *Lump, ILuint Size);
ILboolean ilSaveTiff(const char *FileName);

ILboolean ilLoadWal(const ILstring FileName);
ILboolean ilLoadWalF(ILHANDLE File);
ILboolean ilLoadWalL(ILvoid *Lump, ILuint Size);


#endif//INTERNAL_H