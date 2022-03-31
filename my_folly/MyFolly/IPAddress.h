#pragma once
#include <string>
#include <utility>

namespace myfolly
{
	class IPAddress;

	/**
	 * Pair of IPAddress, netmask
	 */
	typedef std::pair<IPAddress, uint8_t> CIDRNetwork;

	/**
	 * Provides a unified interface for IP addresses.
	 *
	 * @note If you compare 2 IPAddress instances, v4-to-v6-mapped addresses are
	 * compared as V4 addresses.
	 *
	 * @note toLong/fromLong deal in network byte order, use toLongHBO/fromLongHBO
	 * if working in host byte order.
	 *
	 * Example usage:
	 * @code
	 *		IPAddress v4addr("192.0.2.129");
	 *		IPAddress v6map("::ffff:192.0.2.129");
	 *		CHECK(v4addr.inSubnet("192.0.2.0/24") ==
	 *		      v4addr.inSubnet(IPAddress("192.0.2.0"), 24));
	 *		CHECK(v4addr.inSubnet("192.0.2.128/30"));
	 *		CHECK(!v4addr.inSubnet("192.0.2.128/32"));
	 *		CHECK(v4addr.asV4().toLong() == 2164392128);
	 *		CHECK(v4addr.asV4().toLongHBO() == 3221226113);
	 *		CHECK(v4addr.isV4());
	 *		CHECK(v6addr.isV6());
	 *		CHECK(v4addr == v6map);
	 *		CHECK(v6map.isIPv4Mapped());
	 *		CHECK(v4addr.asV4() == IPAddress::createIPv4(v6map));
	 *		CHECK(IPAddress::createIPv6(v4addr) == v6map.asV6());
	 * @encode
	 */
	class IPAddress
	{
	private:
		template <typename F>
		auto pick(F f) const
		{
			return isV4() ? f(asV4()) : isV6() ? f(asV6()) : f(asNone());
		}

		class IPAddressNone
		{
		public:
			bool isZero() const { return true; }
			size_t bitCount() const { return 0; }
			std::string toJson() const
			{
				return "{family:'AF_UNSPEC', addr:'', hash:0}";
			}
			std::size_t hash() const { return std::hash<uint64_t>{}(0); }
			bool isLoopback() const
			{
				throw_exception<InvalidAddressFamilyException>("empty address");
			}
		};
	};
} // namespace myfolly
