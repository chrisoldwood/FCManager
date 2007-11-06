////////////////////////////////////////////////////////////////////////////////
//! \file   Common.hpp
//! \brief  Wrapper include file for the most common header files.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APP_COMMON_HPP
#define APP_COMMON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Application documentation.
//

////////////////////////////////////////////////////////////////////////////////
// System headers.

#include <Core/Common.hpp>		// Core library common headers.
#include <WCL/Common.hpp>		// Windows C++ library common headers.
#include <MDBL/Common.hpp>		// Memory Database library common headers.

////////////////////////////////////////////////////////////////////////////////
// Application common headers.

#include "Resource.h"

////////////////////////////////////////////////////////////////////////////////
// Forward declarations for the most common types.

class CFCMDoc;
class CFCMDB;

#endif // APP_COMMON_HPP
