// **********************************************************************
//
// Copyright (c) 2003-2014 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.interceptor;


public class MySystemException extends Ice.SystemException
{
    public MySystemException()
    {
    }

    public String
    ice_name()
    {
        return "MySystemException";
    }
}