#include "rofl/common/csocket.h"
#include "rofl/common/csocket_plain.h"
#ifdef HAVE_OPENSSL
#include "rofl/common/csocket_openssl.h"
#endif

using namespace rofl;


csocket*
csocket::csocket_factory(
		enum csocket::socket_type_t socket_type, csocket_owner *owner)
{
	switch (socket_type) {
	case SOCKET_TYPE_PLAIN: {
		return new csocket_plain(owner);
	} break;
#ifdef HAVE_OPENSSL
	case SOCKET_TYPE_OPENSSL: {
		return new csocket_openssl(owner);
	} break;
#endif
	default:
		throw eSocketTypeNotFound();
	}
}



cparams
csocket::get_params(
		enum socket_type_t socket_type)
{
	switch (socket_type) {
	case SOCKET_TYPE_PLAIN: {
		return csocket_plain::get_params();
	} break;
#ifdef HAVE_OPENSSL
	case SOCKET_TYPE_OPENSSL: {
		return csocket_openssl::get_params();
	} break;
#endif
	default:
		throw eSocketTypeNotFound();
	}

}


