/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TestModule"
 * 	found in "circle_test.asn1"
 * 	`asn1c -D output -pdu=auto -no-gen-OER -no-gen-example`
 */

#include "Circle.h"

static int
radius_4_constraint(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	unsigned long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const unsigned long *)sptr;
	
	if(1 /* No applicable constraints whatsoever */) {
		(void)value; /* Unused variable */
		/* Nothing is here. See below */
	}
	
	return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeInteger,
 * so here we adjust the DEF accordingly.
 */
static int
memb_radius_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	unsigned long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const unsigned long *)sptr;
	
	if(1 /* No applicable constraints whatsoever */) {
		(void)value; /* Unused variable */
		/* Nothing is here. See below */
	}
	
	return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
}

static asn_per_constraints_t asn_PER_type_radius_constr_4 CC_NOTUSED = {
	{ APC_SEMI_CONSTRAINED,	-1, -1,  0,  0 }	/* (0..MAX) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_radius_constr_4 CC_NOTUSED = {
	{ APC_SEMI_CONSTRAINED,	-1, -1,  0,  0 }	/* (0..MAX) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_specifics_t asn_SPC_radius_specs_4 = {
	0,	0,	0,	0,	0,
	0,	/* Native long size */
	1	/* Unsigned representation */
};
static const ber_tlv_tag_t asn_DEF_radius_tags_4[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_radius_4 = {
	"radius",
	"radius",
	&asn_OP_NativeInteger,
	asn_DEF_radius_tags_4,
	sizeof(asn_DEF_radius_tags_4)
		/sizeof(asn_DEF_radius_tags_4[0]), /* 1 */
	asn_DEF_radius_tags_4,	/* Same as above */
	sizeof(asn_DEF_radius_tags_4)
		/sizeof(asn_DEF_radius_tags_4[0]), /* 1 */
	{ 0, &asn_PER_type_radius_constr_4, radius_4_constraint },
	0, 0,	/* No members */
	&asn_SPC_radius_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_Circle_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Circle, position_x),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"position-x"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Circle, position_y),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"position-y"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Circle, radius),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_radius_4,
		0,
		{ 0, &asn_PER_memb_radius_constr_4,  memb_radius_constraint_1 },
		0, 0, /* No default value */
		"radius"
		},
};
static const ber_tlv_tag_t asn_DEF_Circle_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Circle_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 2 }, /* position-x */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, -1, 1 }, /* position-y */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -2, 0 } /* radius */
};
static asn_SEQUENCE_specifics_t asn_SPC_Circle_specs_1 = {
	sizeof(struct Circle),
	offsetof(struct Circle, _asn_ctx),
	asn_MAP_Circle_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_Circle = {
	"Circle",
	"Circle",
	&asn_OP_SEQUENCE,
	asn_DEF_Circle_tags_1,
	sizeof(asn_DEF_Circle_tags_1)
		/sizeof(asn_DEF_Circle_tags_1[0]), /* 1 */
	asn_DEF_Circle_tags_1,	/* Same as above */
	sizeof(asn_DEF_Circle_tags_1)
		/sizeof(asn_DEF_Circle_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_Circle_1,
	3,	/* Elements count */
	&asn_SPC_Circle_specs_1	/* Additional specs */
};

