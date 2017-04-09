/*
* File: FNV.h
* Author: jtucker
*
* Created on 12_25_16
*/

#ifndef FNV_H
#define FNV_H

#include <array>
#include <vector>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>

#include <mpir.h>
#include <mpirxx.h>

	//Simple definition
	using byte = unsigned char ;
	
	//The requisite prime and seed for FNV1 hash
	static const uint32_t Prime = 0x01000193;
	static const uint32_t Seed = 0x811C9DC5;


	
	//These templates are invaluable conversion templates 
	template< typename T > std::array< byte, sizeof(T) >  to_bytes( const T& object )
	{
			    std::array< byte, sizeof(T) > bytes ;

			    const byte* begin = reinterpret_cast< const byte* >( std::addressof(object) ) ;
			    const byte* end = begin + sizeof(T) ;
			    std::copy( begin, end, std::begin(bytes) ) ;

			    return bytes ;
	}
	
	//These templates must remain as is.
	template< typename T > T& from_bytes( const std::array< byte, sizeof(T) >& bytes, T& object )
	{
			    // http://en.cppreference.com/w/cpp/types/is_trivially_copyable
			    static_assert( std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type" ) ;

			    byte* begin_object = reinterpret_cast< byte* >( std::addressof(object) ) ;
			    std::copy( std::begin(bytes), std::end(bytes), begin_object ) ;

			    return object ;
	}


	//Definition of the FNV class.
	class FNV
	{
		public:

			//Empty constructor not needed. All usage instances are of the static functions.
			FNV();
			
			//This function returns the fnv1a hash of one byte.  Meant to be a sub function
			static uint32_t fnv1a(unsigned char oneByte, uint32_t hash)
			{
				return (oneByte ^ hash) * Prime;
			}
			
			//This function returns the hash of an array of bytes.
			static uint32_t fnv1aArray(const uint32_t bytes[])
			{
				uint32_t hash = Seed;
				for (int i = 0; i < sizeof(bytes); i++) {
					byte b = bytes[i];
					hash = fnv1a(b,hash);
				} 
				return hash;
			}
			
			//This function returns the hash of an MPZ_T number.
			static uint32_t fnv1aHashOfMpz_t(const mpz_t x)
			{
				//Calculations and initializations
				size_t size = (mpz_sizeinbase (x, 2) + CHAR_BIT-1) / CHAR_BIT;
    				std::vector<byte> v(size);
				//Exporting the MPZ_T vector into bytes
    				mpz_export(&v[0], &size, 1, 1, 0, 0, x);
    				v.resize(size);
				//Hash algorithm
				uint32_t hash = Seed;
				for(unsigned int i = 0; i < v.size(); i++)
				{
					byte b = v[i];
					hash = fnv1a(b, hash);
				}					
				return hash;
			}

			
		private:
			

			

	};
#endif
