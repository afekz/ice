// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_VALUE_FACTORY_MANAGER_F_H
#define ICE_VALUE_FACTORY_MANAGER_F_H

#include <IceUtil/Shared.h>

#include <Ice/Handle.h>

namespace IceInternal
{

#ifndef ICE_CPP11_MAPPING
class ValueFactoryWrapper;
IceUtil::Shared* upCast(ValueFactoryWrapper*);
typedef Handle<ValueFactoryWrapper> ValueFactoryWrapperPtr;
#endif

class ValueFactoryManager;
IceUtil::Shared* upCast(ValueFactoryManager*);
typedef Handle<ValueFactoryManager> ValueFactoryManagerPtr;

}

#endif
