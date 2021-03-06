// Copyright 2019 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_TRAITS_MACROS_DEPRECATED_HPP
#define JSONCONS_JSON_TRAITS_MACROS_DEPRECATED_HPP

#include <jsoncons/json_traits_macros.hpp>

#if !defined(JSONCONS_NO_DEPRECATED)

#define JSONCONS_N_MEMBER_TRAITS_DECL JSONCONS_N_MEMBER_TRAITS

#define JSONCONS_TPL_N_MEMBER_TRAITS_DECL JSONCONS_TPL_N_MEMBER_TRAITS

#define JSONCONS_ALL_MEMBER_TRAITS_DECL JSONCONS_ALL_MEMBER_TRAITS

#define JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL JSONCONS_TPL_ALL_MEMBER_TRAITS 

#define JSONCONS_MEMBER_TRAITS_DECL JSONCONS_MEMBER_TRAITS

#define JSONCONS_TPL_MEMBER_TRAITS_DECL JSONCONS_TPL_MEMBER_TRAITS

#define JSONCONS_N_MEMBER_NAMED_TRAITS_DECL JSONCONS_N_MEMBER_NAMED_TRAITS

#define JSONCONS_TPL_N_MEMBER_NAMED_TRAITS_DECL JSONCONS_TPL_N_MEMBER_NAMED_TRAITS

#define JSONCONS_ALL_MEMBER_NAMED_TRAITS_DECL JSONCONS_ALL_MEMBER_NAMED_TRAITS

#define JSONCONS_TPL_ALL_MEMBER_NAMED_TRAITS_DECL JSONCONS_TPL_ALL_MEMBER_NAMED_TRAITS

#define JSONCONS_MEMBER_NAMED_TRAITS_DECL JSONCONS_MEMBER_NAMED_TRAITS

#define JSONCONS_TPL_MEMBER_NAMED_TRAITS_DECL JSONCONS_TPL_MEMBER_NAMED_TRAITS
 
#define JSONCONS_ALL_GETTER_CTOR_TRAITS_DECL JSONCONS_ALL_GETTER_CTOR_TRAITS
 
#define JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS
 
#define JSONCONS_N_GETTER_CTOR_TRAITS_DECL JSONCONS_N_GETTER_CTOR_TRAITS
 
#define JSONCONS_N_ALL_GETTER_CTOR_TRAITS_DECL JSONCONS_N_ALL_GETTER_CTOR_TRAITS
 
#define JSONCONS_ALL_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_ALL_GETTER_CTOR_NAMED_TRAITS
 
#define JSONCONS_TPL_ALL_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_CTOR_NAMED_TRAITS
 
#define JSONCONS_N_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_N_GETTER_CTOR_NAMED_TRAITS
 
#define JSONCONS_TPL_N_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_TPL_N_GETTER_CTOR_NAMED_TRAITS

#define JSONCONS_ENUM_TRAITS_DECL JSONCONS_ENUM_TRAITS

#define JSONCONS_ENUM_NAMED_TRAITS_DECL JSONCONS_ENUM_NAMED_TRAITS

#define JSONCONS_N_GETTER_SETTER_TRAITS_DECL JSONCONS_N_GETTER_SETTER_TRAITS

#define JSONCONS_TPL_N_GETTER_SETTER_TRAITS_DECL JSONCONS_TPL_N_GETTER_SETTER_TRAITS

#define JSONCONS_ALL_GETTER_SETTER_TRAITS_DECL JSONCONS_ALL_GETTER_SETTER_TRAITS

#define JSONCONS_TPL_ALL_GETTER_SETTER_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_SETTER_TRAITS

#define JSONCONS_GETTER_SETTER_TRAITS_DECL JSONCONS_GETTER_SETTER_TRAITS

#define JSONCONS_TPL_GETTER_SETTER_TRAITS_DECL JSONCONS_TPL_GETTER_SETTER_TRAITS
 
#define JSONCONS_N_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_N_GETTER_SETTER_NAMED_TRAITS
 
#define JSONCONS_TPL_N_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_TPL_N_GETTER_SETTER_NAMED_TRAITS
 
#define JSONCONS_ALL_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_ALL_GETTER_SETTER_NAMED_TRAITS
 
#define JSONCONS_TPL_ALL_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_SETTER_NAMED_TRAITS

#define JSONCONS_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_GETTER_SETTER_NAMED_TRAITS
 
#define JSONCONS_TPL_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_TPL_GETTER_SETTER_NAMED_TRAITS

#define JSONCONS_POLYMORPHIC_TRAITS_DECL JSONCONS_POLYMORPHIC_TRAITS

#define JSONCONS_TYPE_TRAITS_DECL JSONCONS_MEMBER_TRAITS_DECL
#define JSONCONS_NONDEFAULT_MEMBER_TRAITS_DECL JSONCONS_ALL_MEMBER_TRAITS_DECL
#define JSONCONS_TEMPLATE_STRICT_MEMBER_TRAITS_DECL JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL

#define JSONCONS_MEMBER_TRAITS_NAMED_DECL                        JSONCONS_MEMBER_NAMED_TRAITS_DECL                   
#define JSONCONS_STRICT_MEMBER_TRAITS_NAMED_DECL                 JSONCONS_ALL_MEMBER_NAMED_TRAITS_DECL            
#define JSONCONS_TEMPLATE_MEMBER_TRAITS_DECL                     JSONCONS_TPL_MEMBER_TRAITS_DECL                     
#define JSONCONS_STRICT_TEMPLATE_MEMBER_TRAITS_DECL              JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL              
#define JSONCONS_TEMPLATE_MEMBER_TRAITS_NAMED_DECL               JSONCONS_TPL_MEMBER_NAMED_TRAITS_DECL               
#define JSONCONS_STRICT_TEMPLATE_MEMBER_TRAITS_NAMED_DECL        JSONCONS_TPL_ALL_MEMBER_NAMED_TRAITS_DECL        
#define JSONCONS_ENUM_TRAITS_NAMED_DECL                          JSONCONS_ENUM_NAMED_TRAITS_DECL                     
#define JSONCONS_GETTER_CTOR_TRAITS_NAMED_DECL                   JSONCONS_ALL_GETTER_CTOR_NAMED_TRAITS_DECL              
#define JSONCONS_TEMPLATE_GETTER_CTOR_TRAITS_DECL                JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS_DECL                
#define JSONCONS_TEMPLATE_GETTER_CTOR_TRAITS_NAMED_DECL          JSONCONS_TPL_ALL_GETTER_CTOR_NAMED_TRAITS_DECL          
#define JSONCONS_GETTER_SETTER_TRAITS_NAMED_DECL                 JSONCONS_ALL_GETTER_SETTER_NAMED_TRAITS_DECL            
#define JSONCONS_STRICT_GETTER_SETTER_TRAITS_NAMED_DECL          JSONCONS_ALL_GETTER_SETTER_NAMED_TRAITS_DECL     
#define JSONCONS_TEMPLATE_GETTER_SETTER_TRAITS_NAMED_DECL        JSONCONS_TPL_GETTER_SETTER_NAMED_TRAITS_DECL        
#define JSONCONS_STRICT_TEMPLATE_GETTER_SETTER_TRAITS_NAMED_DECL JSONCONS_TPL_ALL_GETTER_SETTER_NAMED_TRAITS_DECL 
#define JSONCONS_STRICT_TPL_MEMBER_TRAITS_DECL                   JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL
#define JSONCONS_STRICT_TPL_MEMBER_NAMED_TRAITS_DECL             JSONCONS_TPL_ALL_MEMBER_NAMED_TRAITS_DECL
#define JSONCONS_STRICT_TPL_GETTER_SETTER_NAMED_TRAITS_DECL      JSONCONS_TPL_ALL_GETTER_SETTER_NAMED_TRAITS_DECL

#define JSONCONS_STRICT_MEMBER_TRAITS_DECL JSONCONS_ALL_MEMBER_TRAITS_DECL 
#define JSONCONS_TPL_STRICT_MEMBER_TRAITS_DECL JSONCONS_TPL_ALL_MEMBER_TRAITS_DECL
#define JSONCONS_STRICT_MEMBER_NAMED_TRAITS_DECL JSONCONS_ALL_MEMBER_NAMED_TRAITS_DECL
#define JSONCONS_TPL_STRICT_MEMBER_NAMED_TRAITS_DECL JSONCONS_ALL_STRICT_MEMBER_NAMED_TRAITS_DECL
#define JSONCONS_STRICT_PROPERTY_TRAITS_DECL JSONCONS_ALL_GETTER_SETTER_TRAITS_DECL
#define JSONCONS_TPL_STRICT_PROPERTY_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_SETTER_TRAITS_DECL
#define JSONCONS_STRICT_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_ALL_GETTER_SETTER_NAMED_TRAITS_DECL
#define JSONCONS_TPL_STRICT_GETTER_SETTER_NAMED_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_SETTER_NAMED_TRAITS_DECL
#define JSONCONS_GETTER_CTOR_TRAITS_DECL JSONCONS_ALL_GETTER_CTOR_TRAITS_DECL
#define JSONCONS_TPL_GETTER_CTOR_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS_DECL  
#define JSONCONS_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_ALL_GETTER_CTOR_NAMED_TRAITS_DECL
#define JSONCONS_TPL_GETTER_CTOR_NAMED_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_CTOR_NAMED_TRAITS_DECL
#define JSONCONS_N_PROPERTY_TRAITS_DECL JSONCONS_N_GETTER_SETTER_TRAITS_DECL
#define JSONCONS_ALL_PROPERTY_TRAITS_DECL JSONCONS_ALL_GETTER_SETTER_TRAITS_DECL
#define JSONCONS_TPL_N_PROPERTY_TRAITS_DECL JSONCONS_TPL_N_GETTER_SETTER_TRAITS_DECL
#define JSONCONS_TPL_ALL_PROPERTY_TRAITS_DECL JSONCONS_TPL_ALL_GETTER_SETTER_TRAITS_DECL

#endif

#endif
