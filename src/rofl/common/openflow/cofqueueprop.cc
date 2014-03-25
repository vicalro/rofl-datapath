/*
 * ofqueueprop.cc
 *
 *  Created on: 29.04.2013
 *      Author: andi
 */

#include "rofl/common/openflow/cofqueueprop.h"

using namespace rofl::openflow;

cofqueue_prop::cofqueue_prop(
		uint8_t of_version) :
				of_version(of_version)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		resize(sizeof(struct openflow10::ofp_queue_prop_header));
	} break;
	case openflow12::OFP_VERSION: {
		resize(sizeof(struct openflow12::ofp_queue_prop_header));
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	set_length(memlen());
}



cofqueue_prop::~cofqueue_prop()
{

}



cofqueue_prop::cofqueue_prop(
		cofqueue_prop const& qp)
{
	*this = qp;
}



cofqueue_prop&
cofqueue_prop::operator =(
		cofqueue_prop const& qp)
{
	if (this == &qp)
		return *this;

	cmemory::operator =(qp);

	ofq_header = somem();
	of_version = qp.of_version;

	return *this;
}



uint8_t*
cofqueue_prop::resize(size_t len)
{
	ofq_header = cmemory::resize(len);
	return somem();
}



size_t
cofqueue_prop::length() const
{
	return memlen();
}



void
cofqueue_prop::pack(uint8_t *buf, size_t buflen) const
{
	if (buflen < memlen())
		throw eInval();

	switch (of_version) {
	case openflow10::OFP_VERSION: {
		memcpy(buf, somem(),memlen());
	} break;
	case openflow12::OFP_VERSION: {
		memcpy(buf, somem(),memlen());
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}



void
cofqueue_prop::unpack(uint8_t *buf, size_t buflen)
{
	if (memlen() < buflen)
		resize(buflen);

	switch (of_version) {
	case openflow10::OFP_VERSION: {
		memcpy(somem(), buf, buflen);
	} break;
	case openflow12::OFP_VERSION: {
		memcpy(somem(), buf, buflen);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	} break;
	}

	ofq_header = somem();
}



uint16_t
cofqueue_prop::get_property() const
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		return be16toh(ofq10_header->property);
	} break;
	case openflow12::OFP_VERSION: {
		return be16toh(ofq12_header->property);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}


void
cofqueue_prop::set_property(uint16_t property)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		ofq10_header->property = htobe16(property);
	} break;
	case openflow12::OFP_VERSION: {
		ofq12_header->property = htobe16(property);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}



uint16_t
cofqueue_prop::get_length() const
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		return be16toh(ofq10_header->len);
	} break;
	case openflow12::OFP_VERSION: {
		return be16toh(ofq12_header->len);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}



void
cofqueue_prop::set_length(uint16_t len)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		ofq10_header->len = htobe16(len);
	} break;
	case openflow12::OFP_VERSION: {
		ofq12_header->len = htobe16(len);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}





cofqueue_prop_min_rate::cofqueue_prop_min_rate(
	uint8_t of_version,
	uint16_t min_rate) :
		cofqueue_prop(of_version)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		resize(sizeof(struct openflow10::ofp_queue_prop_min_rate));
	} break;
	case openflow12::OFP_VERSION: {
		resize(sizeof(struct openflow12::ofp_queue_prop_min_rate));
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	set_property(rofl::openflow13::OFPQT_MIN_RATE);
	set_length(memlen());
	set_rate(min_rate);
}




cofqueue_prop_min_rate::~cofqueue_prop_min_rate()
{

}



cofqueue_prop_min_rate::cofqueue_prop_min_rate(
	cofqueue_prop_min_rate const& qp) :
		cofqueue_prop(qp.of_version)
{
	*this = qp;
}



cofqueue_prop_min_rate&
cofqueue_prop_min_rate::operator= (
		cofqueue_prop const& qp)
{
	if (this == &qp)
		return *this;

	if (rofl::openflow13::OFPQT_MIN_RATE != qp.get_property())
		throw eInval();

	unpack(qp.somem(), qp.memlen());

	return *this;
}



uint8_t*
cofqueue_prop_min_rate::resize(size_t len)
{
	ofq_min_rate = cofqueue_prop::resize(len);
	return somem();
}



void
cofqueue_prop_min_rate::pack(uint8_t *buf, size_t buflen) const
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		if (buflen < sizeof(struct openflow10::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow12::OFP_VERSION: {
		if (buflen < sizeof(struct openflow12::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}

	cofqueue_prop::pack(buf, buflen);
}



void
cofqueue_prop_min_rate::unpack(uint8_t *buf, size_t buflen)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		if (buflen < sizeof(struct openflow10::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow12::OFP_VERSION: {
		if (buflen < sizeof(struct openflow12::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}

	cofqueue_prop::unpack(buf, buflen);
	ofq_min_rate = somem();
}



uint16_t
cofqueue_prop_min_rate::get_rate() const
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		return be16toh(ofq10_min_rate->rate);
	} break;
	case openflow12::OFP_VERSION: {
		return be16toh(ofq12_min_rate->rate);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}



void
cofqueue_prop_min_rate::set_rate(uint16_t rate)
{
	switch (of_version) {
	case openflow10::OFP_VERSION: {
		ofq10_min_rate->rate = htobe16(rate);
	} break;
	case openflow12::OFP_VERSION: {
		ofq12_min_rate->rate = htobe16(rate);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}



cofqueue_prop_max_rate::cofqueue_prop_max_rate(
	uint8_t of_version,
	uint16_t max_rate) :
		cofqueue_prop(of_version)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		resize(sizeof(struct openflow12::ofp_queue_prop_min_rate));
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	ofq_max_rate = somem();
	set_property(rofl::openflow13::OFPQT_MAX_RATE);
	set_length(memlen());
	set_rate(max_rate);
}




cofqueue_prop_max_rate::~cofqueue_prop_max_rate()
{

}



cofqueue_prop_max_rate::cofqueue_prop_max_rate(
	cofqueue_prop_max_rate const& qp) :
		cofqueue_prop(qp.of_version)
{
	*this = qp;
}



cofqueue_prop_max_rate&
cofqueue_prop_max_rate::operator= (
	cofqueue_prop const& qp)
{
	if (this == &qp)
		return *this;

	switch (of_version) {
	case openflow12::OFP_VERSION: {
		if (openflow12::OFPQT_MAX_RATE != qp.get_property())
			throw eInval();
	} break;
	case openflow13::OFP_VERSION: {
		if (openflow13::OFPQT_MAX_RATE != qp.get_property())
			throw eInval();
	} break;
	default:
		throw eBadVersion();
	}

	unpack(qp.somem(), qp.memlen());

	return *this;
}



uint8_t*
cofqueue_prop_max_rate::resize(size_t len)
{
	ofq_max_rate = cofqueue_prop::resize(len);
	return somem();
}



void
cofqueue_prop_max_rate::pack(uint8_t *buf, size_t buflen) const
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		if (buflen < sizeof(struct openflow12::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}

	cofqueue_prop::pack(buf, buflen);
}



void
cofqueue_prop_max_rate::unpack(uint8_t *buf, size_t buflen)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		if (buflen < sizeof(struct openflow12::ofp_queue_prop_min_rate))
			throw eInval();
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}

	cofqueue_prop::unpack(buf, buflen);
	ofq_max_rate = somem();
}



uint16_t
cofqueue_prop_max_rate::get_rate() const
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		return be16toh(ofq12_max_rate->rate);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}



void
cofqueue_prop_max_rate::set_rate(uint16_t rate)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		ofq12_max_rate->rate = htobe16(rate);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}




cofqueue_prop_expr::cofqueue_prop_expr(
	uint8_t of_version) :
		cofqueue_prop(of_version),
		body(0)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		resize(sizeof(struct openflow12::ofp_queue_prop_experimenter));
		ofq_expr = somem();
		set_property(openflow12::OFPQT_EXPERIMENTER);
		set_length(memlen());
	} break;
	case openflow13::OFP_VERSION: {
		assert(0);
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}




cofqueue_prop_expr::~cofqueue_prop_expr()
{

}



cofqueue_prop_expr::cofqueue_prop_expr(
	cofqueue_prop_expr const& qp) :
		cofqueue_prop(qp.of_version),
		body(0)
{
	*this = qp;
}



cofqueue_prop_expr&
cofqueue_prop_expr::operator= (
	cofqueue_prop_expr const& qp)
{
	if (this == &qp)
		return *this;

	cofqueue_prop::operator=(qp);
	ofq_expr = somem();
	body = qp.body;

	return *this;
}



cofqueue_prop_expr&
cofqueue_prop_expr::operator= (
	cofqueue_prop const& qp)
{
	if (this == &qp)
		return *this;

	switch (of_version) {
	case openflow12::OFP_VERSION: {
		if (openflow12::OFPQT_EXPERIMENTER != qp.get_property())
			throw eInval();
	} break;
	default:
		assert(0);
		throw eBadVersion();
	}

	unpack(qp.somem(), qp.memlen());

	return *this;
}


size_t
cofqueue_prop_expr::length() const
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		return (sizeof(struct openflow12::ofp_queue_prop_experimenter) + body.memlen());
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}



void
cofqueue_prop_expr::pack(uint8_t *buf, size_t buflen) const
{
	if (buflen < length())
		throw eInval();

	switch (of_version) {
	case openflow12::OFP_VERSION: {
		memcpy(buf, somem(), memlen());
		memcpy(buf + memlen(), body.somem(), body.memlen());
		struct openflow12::ofp_queue_prop_header* qp = (struct openflow12::ofp_queue_prop_header*)buf;
		qp->len = htobe16(length());
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}



void
cofqueue_prop_expr::unpack(uint8_t *buf, size_t buflen)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		if (buflen < sizeof(struct openflow12::ofp_queue_prop_experimenter))
			throw eInval();
		cofqueue_prop::resize(sizeof(struct openflow12::ofp_queue_prop_experimenter));
		ofq_expr = somem();
		memcpy(somem(), buf, sizeof(struct openflow12::ofp_queue_prop_experimenter));
		if (buflen > sizeof(struct openflow12::ofp_queue_prop_experimenter)) {
			body.resize(buflen - sizeof(struct openflow12::ofp_queue_prop_experimenter));
			memcpy(body.somem(), buf + sizeof(struct openflow12::ofp_queue_prop_experimenter),
					body.memlen());
		}
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}

	cofqueue_prop::unpack(buf, buflen);
	ofq_expr = somem();
}



uint32_t
cofqueue_prop_expr::get_expr() const
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		return be32toh(ofq12_expr->experimenter);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
	return 0;
}



void
cofqueue_prop_expr::set_expr(uint32_t expr)
{
	switch (of_version) {
	case openflow12::OFP_VERSION: {
		ofq12_expr->experimenter = htobe32(expr);
	} break;
	case openflow13::OFP_VERSION: {
		throw eNotImplemented();
	} break;
	default: {
		throw eBadVersion();
	}
	}
}



rofl::cmemory&
cofqueue_prop_expr::get_body()
{
	return body;
}


