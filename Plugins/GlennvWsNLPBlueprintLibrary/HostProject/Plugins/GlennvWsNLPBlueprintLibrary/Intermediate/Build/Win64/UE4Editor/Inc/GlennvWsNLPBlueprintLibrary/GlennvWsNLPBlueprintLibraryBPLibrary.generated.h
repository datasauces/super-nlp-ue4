
// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GLENNVWSNLPBLUEPRINTLIBRARY_GlennvWsNLPBlueprintLibraryBPLibrary_generated_h
#error "GlennvWsNLPBlueprintLibraryBPLibrary.generated.h already included, missing '#pragma once' in GlennvWsNLPBlueprintLibraryBPLibrary.h"
#endif
#define GLENNVWSNLPBLUEPRINTLIBRARY_GlennvWsNLPBlueprintLibraryBPLibrary_generated_h

#define G__Dev_nlp_ue4_Plugins_GlennvWsNLPBlueprintLibrary_HostProject_Plugins_GlennvWsNLPBlueprintLibrary_Source_GlennvWsNLPBlueprintLibrary_Public_GlennvWsNLPBlueprintLibraryBPLibrary_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetFileListOfRootFolder) \
	{ \
		P_GET_TARRAY_REF(FString,Z_Param_Out_Files); \
		P_GET_PROPERTY(UStrProperty,Z_Param_RootFolderFullPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Ext); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UGlennvWsNLPBlueprintLibraryBPLibrary::GetFileListOfRootFolder(Z_Param_Out_Files,Z_Param_RootFolderFullPath,Z_Param_Ext); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGlennvWsNLPBlueprintLibrarySampleFunction) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Param); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=UGlennvWsNLPBlueprintLibraryBPLibrary::GlennvWsNLPBlueprintLibrarySampleFunction(Z_Param_Param); \
		P_NATIVE_END; \
	}


#define G__Dev_nlp_ue4_Plugins_GlennvWsNLPBlueprintLibrary_HostProject_Plugins_GlennvWsNLPBlueprintLibrary_Source_GlennvWsNLPBlueprintLibrary_Public_GlennvWsNLPBlueprintLibraryBPLibrary_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetFileListOfRootFolder) \
	{ \
		P_GET_TARRAY_REF(FString,Z_Param_Out_Files); \
		P_GET_PROPERTY(UStrProperty,Z_Param_RootFolderFullPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Ext); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UGlennvWsNLPBlueprintLibraryBPLibrary::GetFileListOfRootFolder(Z_Param_Out_Files,Z_Param_RootFolderFullPath,Z_Param_Ext); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGlennvWsNLPBlueprintLibrarySampleFunction) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Param); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=UGlennvWsNLPBlueprintLibraryBPLibrary::GlennvWsNLPBlueprintLibrarySampleFunction(Z_Param_Param); \
		P_NATIVE_END; \
	}
