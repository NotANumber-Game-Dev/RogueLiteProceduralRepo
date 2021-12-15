// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadXMLLevelDetail.h"


/*
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("succeed!"));
}

void UReadXMLLevelDetail::ReadXmlFile(const FString& XmlPath)
{
	FXmlFile* XmlFile = new FXmlFile(XmlPath);
	FXmlNode* RootNode = XmlFile->GetRootNode();
	AssetNodes = RootNode->GetChildrenNodes();
	for (FXmlNode* node : AssetNodes)
	{
		ChildNodes = node->GetChildrenNodes();
		AssetContent = node->GetContent();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AssetContent);
		for (FXmlNode* childNode : ChildNodes)
		{
			ChildContent = childNode->GetContent();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, ChildContent);
		}
	}
}

void UReadXMLLevelDetail::getAssetNodes(TArray<FXmlNode*> &var)
{
	
}

TArray<FXmlNode*> UReadXMLLevelDetail::getChildNodes()
{
	return ChildNodes;
}

FString UReadXMLLevelDetail::getAssetContent()
{
	return AssetContent;
}

FString UReadXMLLevelDetail::getChildContent()
{
	return ChildContent;
}
*/