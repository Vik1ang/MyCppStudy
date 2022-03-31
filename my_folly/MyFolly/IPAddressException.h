#pragma once

#include <exception>
#include <stdexcept>

namespace myfolly
{
	/*
	 * Error codes for non-throwing interface of IPAddress family of functions.
	 */
	enum class IPAddressFormatError { INVALID_IP, UNSUPPORTED_ADDR_FAMILY };

	/**
	 * Wraps error from parsing IP/MASK string
	 */
	enum class CIDRNetworkError
	{
		INVALID_DEFAULT_CIDR,
		INVALID_IP_SLASH_CIRD,
		INVALID_IP,
		INVALID_CIDR,
		CIDR_MISMATCH,
	};

	/**
	 * Exception for invalid IP addresses.
	 */
	class MYFOLLY_EXPORT IPAddressFormatException : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	class MYFOLLY_EXPORT InvalidAddressFamilyException : public IPAddressFormatException
	{
	public:
		explicit InvalidAddressFamilyException(const char* msg) :
			IPAddressFormatException{ msg } {}
		explicit InvalidAddressFamilyException(const std::string& msg) noexcept :
			IPAddressFormatException{ msg } {}
		explicit InvalidAddressFamilyException(sa_family_t family) noexcept :
			InvalidAddressFamilyException(
				"Address family " + detail::familyNameStr(family) +
				" is not AF_INET or AF_INET6"
			) {}
	};
} // namespace myfolly
