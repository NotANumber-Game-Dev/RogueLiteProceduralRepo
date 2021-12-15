// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"

#include "Runtime/XmlParser/Public/XmlFile.h"
#include "Runtime/XmlParser/Public/XmlNode.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadXMLLevelDetail.generated.h"

/**
 * https://www.fatalerrors.org/a/text-file-profile-json-file-xml-file-read-and-write-in-ue4.html
 * PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "XmlParser" });
 */
UCLASS()
class CONTROLLEDMAIN_API UReadXMLLevelDetail : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	//static TArray<FXmlNode*> AssetNodes;
	//static TArray<FXmlNode*> ChildNodes;
	//static FString AssetContent;
	//static FString ChildContent;

public:
	//UE4 reads xml files
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static void CreateXmlFile();
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static void ReadXmlFile(const FString& XmlPath);
	//
	////FALTA AFEGIR ELS NODES TAGS I LA RESTA DE COSES COM A UPROPERTIES PERQUE ES PUGUI ACCEDIR
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static void getAssetNodes(TArray<FXmlNode*> &var);
	//
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static TArray<FXmlNode*> getChildNodes();
	//
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static FString getAssetContent();
	//
	//UFUNCTION(BlueprintCallable, Category = "Test")
	//static FString getChildContent();

};
