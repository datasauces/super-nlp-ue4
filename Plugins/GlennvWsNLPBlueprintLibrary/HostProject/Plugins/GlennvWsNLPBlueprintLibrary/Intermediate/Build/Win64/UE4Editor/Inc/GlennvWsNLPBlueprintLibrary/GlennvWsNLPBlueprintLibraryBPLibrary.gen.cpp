// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GlennvWsNLPBlueprintLibrary/Public/GlennvWsNLPBlueprintLibraryBPLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGlennvWsNLPBlueprintLibraryBPLibrary() {}
// Cross Module References
	GLENNVWSNLPBLUEPRINTLIBRARY_API UClass* Z_Construct_UClass_UGlennvWsNLPBlueprintLibraryBPLibrary_NoRegister();
	GLENNVWSNLPBLUEPRINTLIBRARY_API UClass* Z_Construct_UClass_UGlennvWsNLPBlueprintLibraryBPLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_GlennvWsNLPBlueprintLibrary();
	GLENNVWSNLPBLUEPRINTLIBRARY_API UFunction* Z_Construct_UFunction_UGlennvWsNLPBlueprintLibraryBPLibrary_GetFileListOfRootFolder();
	GLENNVWSNLPBLUEPRINTLIBRARY_API UFunction* Z_Construct_UFunction_UGlennvWsNLPBlueprintLibraryBPLibrary_GlennvWsNLPBlueprintLibrarySampleFunction();
// End Cross Module References
	void UGlennvWsNLPBlueprintLibraryBPLibrary::StaticRegisterNativesUGlennvWsNLPBlueprintLibraryBPLibrary()
	{
		UClass* Class = UGlennvWsNLPBlueprintLibraryBPLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetFileListOfRootFolder", &UGlennvWsNLPBlueprintLibraryBPLibrary::execGetFileListOfRootFolder },
			{ "GlennvWsNLPBlueprintLibrarySampleFunction", &UGlennvWsNLPBlueprintLibraryBPLibrary::execGlennvWsNLPBlueprintLibrarySampleFunction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGlennvWsNLPBlueprintLibraryBPLibrary_GetFileListOfRootFolder_Statics
	{
		struct GlennvWsNLPBlueprintLibraryBPLibrary_eventGetFileListOfRootFolder_Parms
		{
			TArray<FString> Files;
			FString RootFolderFullPath;
			FString Ext;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStr