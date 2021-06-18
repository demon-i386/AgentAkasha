// SYSTEM == 0 : windows
// SYSTEM == 1 : linux 
#define SYSTEM 1
#if SYSTEM == 0
	#undef UNICODE
	#define UNICODE
	#include <windows.h>
	#include <wchar.h>
	#include "wbranch.h"
	#include <securitybaseapi.h>
	#include <ntsecapi.h>
	#define wchar_t wchar_t
#else 
	#include <iostream>
	#include <unistd.h>
	#include <linux/icmp.h>
	#include "lbranch.h"
	#define wchar_t char
#endif

#include <stdio.h>

int main(int argc, wchar_t **argv){
	#if SYSTEM == 0
		/*
		NTSTATUS LsaOpenPolicy(
			PLSA_UNICODE_STRING    SystemName,
			PLSA_OBJECT_ATTRIBUTES ObjectAttributes,
			ACCESS_MASK            DesiredAccess,
			PLSA_HANDLE            PolicyHandle
		);
		*/
		bool userPrivileges;
		LSA_HANDLE lsPolicy;
		LSA_UNICODE_STRING lsaUnicodeStr[2];
		LSA_OBJECT_ATTRIBUTES objectAttributes = {0};
		PSID securityIdentifier;

		NTSTATUS currentUserStatus = LsaOpenPolicy(NULL, &objectAttributes, POLICY_ALL_ACCESS, &lsPolicy);
		if(LsaNtStatusToWinError(currentUserStatus) != ERROR_SUCCESS){
			userPrivileges = true;
		}
		else{
			userPrivileges = false;
		}
		printf("%d", userPrivileges);
	#else
		uid_t uUid = getuid(), uPid = getpid(), uGid = getgid(), eUid=geteuid();
		if(uUid<=0||uUid!=eUid){
			printf("Root");
		}
		else{
			printf("User");
		}
	#endif



}
