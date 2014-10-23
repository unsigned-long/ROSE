/* Declarations for RMD - ROSE binary format */

#ifndef ROSE_RMD_H
#define ROSE_RMD_H

#include <stdint.h>

/* Versions */
typedef struct RMDVersion {
	unsigned char maj;
	unsigned char min;
} RMDVersion;

/* Base types */
typedef uint8_t R_Byte;
typedef int32_t R_Word;

/* Address types */
typedef uint16_t RA_Symbol;
typedef uint32_t RA_Array;
typedef uint32_t RA_Text;

/* Other types */
typedef int16_t  R_TextOffset;

/* Information about sector sizes */
typedef struct RMDSectorSize {
	RA_Text text;              /* text sector size      */
	RA_Array str;              /* string sector size    */
	RA_Symbol sym;             /* symbol sector size    */
	uint8_t exp;               /* export table size     */
	uint8_t ptbl;              /* procedure table size  */
	uint8_t mtbl;              /* module table size     */
	uint8_t imp;               /* import table size     */
} RMDSectorSize;

/* RMD header */
typedef struct RMDHeader {
	unsigned char ident[4];    /* signature                 */
	RMDVersion rmd_version;    /* ROSE version              */
	RA_Symbol name;            /* module name               */
	RA_Symbol parent;          /* parent module name        */
	RMDVersion version;        /* module version            */
	RMDSectorSize sizes;       /* sizes of all sectors      */
	uint8_t flags;             /* various flags             */
	uint8_t datac;             /* data count                */
	uint32_t size;             /* size of (module - header) */
	uint32_t debug;            /* debug section size        */
	char pad[8];               /* for future expanding      */
} RMDHeader;

/* RMD signature */
#define RMD_H_IDENT1		'R'
#define RMD_H_IDENT2		'M'
#define RMD_H_IDENT3		'D'
#define RMD_H_IDENT4		0x1F

/* Segment order:
 * exp;
 * ptbl;
 * mtbl;
 * imp;
 * text;
 * sym;
 * str.
 */

/* #ptbl entry */
typedef struct RMDProcedure {
	uint32_t addr;
	uint8_t argc;
	uint8_t varc;
} RMDProcedure;

/* #exp entry */
typedef struct RMDExport {
	RA_Symbol name;
	RA_Symbol proto;
	uint8_t idx;
} RMDExport;

/* #mtbl entry */
typedef struct RMDModule {
	RA_Symbol name;
	RMDVersion version;
} RMDModule;

/* #imp entry */
typedef struct RMDImport {
	RA_Symbol name;
	uint8_t module;
	uint8_t slot;
} RMDImport;

/* #str entry */
typedef struct RMDString {
	uint32_t len;
	char str[1];
} RMDString;

#endif

