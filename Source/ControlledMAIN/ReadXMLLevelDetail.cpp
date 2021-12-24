// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadXMLLevelDetail.h"



void UReadXMLLevelDetail::CreateXmlFile()
{
	const FString XmlContent = "<DocumentElement>\n<Infor>\n< ID>xml </ID >\n<Name>file</Name>\n<Content>cccc</Content>\n</Infor>\n</DocumentElement>";
	FXmlFile* WriteXml = new FXmlFile(XmlContent, EConstructMethod::ConstructFromBuffer);
	if (WriteXml == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("fail!"));
		return;
	}
	WriteXml->Save(FPaths::ProjectContentDir() + "xml.xml");
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("succeed!"));
}

TArray<FString> UReadXMLLevelDetail::ReadTag = TArray<FString>();
TArray<FString> UReadXMLLevelDetail::ReadChildTag = TArray<FString>();
TArray<FString> UReadXMLLevelDetail::ReadContent = TArray<FString>();
TArray<FString> UReadXMLLevelDetail::ReadChildContent = TArray<FString>();
TArray<FString> UReadXMLLevelDetail::StringInstancedMeshes = TArray<FString>();
TArray<FString> UReadXMLLevelDetail::StringRootAttributes = TArray<FString>();



void UReadXMLLevelDetail::ReadXmlFile(const FString& XmlPath)
{
	FXmlFile* XmlFile = new FXmlFile(XmlPath);
	FXmlNode* RootNode = XmlFile->GetRootNode();
	TArray<FXmlAttribute> RootAttributes = RootNode->GetAttributes();
	for (int i = 0; i < RootAttributes.Num(); i++)
	{
		StringRootAttributes.Add(RootAttributes[i].GetValue());
	}
	TArray<FXmlNode*> AssetNodes = RootNode->GetChildrenNodes();
	for (FXmlNode* node : AssetNodes)
	{
		TArray<FXmlNode*> ChildNodes = node->GetChildrenNodes();
		FString AssetContent = node->GetContent();
		FString TagContent = node->GetTag();
		ReadTag.Add(TagContent);
		ReadContent.Add(AssetContent);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AssetContent);
		for (FXmlNode* childNode : ChildNodes)
		{
			FString ChildContent = childNode->GetContent();
			FString ChildTagContent = childNode->GetTag();
			ReadChildContent.Add(ChildContent);
			ReadChildTag.Add(ChildTagContent);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, ChildContent);
		}
	}
}

void UReadXMLLevelDetail::getTag(TArray<FString>& var)
{
	var.Reset(0);
	var.Append(ReadTag);
}

void UReadXMLLevelDetail::getChildTag(TArray<FString>& var)
{
	var.Reset(0);
	var.Append(ReadChildTag);
}

void UReadXMLLevelDetail::getContent(TArray<FString>& var)
{
	var.Reset(0);
	var.Append(ReadContent);
}

void UReadXMLLevelDetail::getChildContent(TArray<FString>& var)
{
	var.Reset(0);
	var.Append(ReadChildContent);
}

void UReadXMLLevelDetail::getMeshesToSpawn(TArray<FString>& var)
{
	ReadContent[3].ParseIntoArray(StringInstancedMeshes, TEXT(","), false);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, StringInstancedMeshes[0]);

	var.Reset(0);
	var.Append(StringInstancedMeshes);
}

void UReadXMLLevelDetail::getRootAttributes(TArray<FString>& var)
{
	//var.Empty();
	var.Reset(0);
	var.Append(StringRootAttributes);
}
