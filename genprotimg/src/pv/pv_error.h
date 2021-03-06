/*
 * PV error related definitions and functions
 *
 * Copyright IBM Corp. 2020
 *
 * s390-tools is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef PV_ERROR_H
#define PV_ERROR_H

#include <glib.h>

GQuark pv_error_quark(void);
GQuark pv_parse_error_quark(void);
GQuark pv_component_error_quark(void);
GQuark pv_crypto_error_quark(void);
GQuark pv_image_error_quark(void);

#define PV_ERROR	   pv_error_quark()
#define PV_PARSE_ERROR	   pv_parse_error_quark()
#define PV_CRYPTO_ERROR	   pv_crypto_error_quark()
#define PV_COMPONENT_ERROR pv_component_error_quark()
#define PV_IMAGE_ERROR	   pv_image_error_quark()

typedef enum {
	PV_ERROR_IPIB_SIZE,
	PV_ERROR_PV_HDR_SIZE,
	PV_ERROR_INTERNAL,
} PvErrors;

typedef enum {
	PV_PARSE_ERROR_OK = 0,
	PV_PARSE_ERROR_SYNTAX,
	PR_PARSE_ERROR_INVALID_ARGUMENT,
	PR_PARSE_ERROR_MISSING_ARGUMENT,
} PvParseErrors;

typedef enum {
	PV_COMPONENT_ERROR_UNALIGNED,
	PV_COMPONENT_ERROR_FINALIZED,
} PvComponentErrors;

typedef enum {
	PV_IMAGE_ERROR_OFFSET,
	PV_IMAGE_ERROR_FINALIZED,
} PvImageErrors;

typedef enum {
	PV_CRYPTO_ERROR_VERIFICATION,
	PV_CRYPTO_ERROR_INIT,
	PV_CRYPTO_ERROR_READ_CERTIFICATE,
	PV_CRYPTO_ERROR_INTERNAL,
	PV_CRYPTO_ERROR_DERIVE,
	PV_CRYPTO_ERROR_KEYGENERATION,
	PV_CRYPTO_ERROR_RANDOMIZATION,
	PV_CRYPTO_ERROR_INVALID_PARM,
	PV_CRYPTO_ERROR_INVALID_KEY_SIZE,
} PvCryptoErrors;

#endif
