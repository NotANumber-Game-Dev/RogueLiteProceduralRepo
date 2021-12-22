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
TArray<UInstancedStaticMeshComponent*> UReadXMLLevelDetail::InstancedMeshes= TArray<UInstancedStaticMeshComponent*>();





void UReadXMLLevelDetail::ReadXmlFile(const FString& XmlPath)
{
	FXmlFile* XmlFile = new FXmlFile(XmlPath);
	FXmlNode* RootNode = XmlFile->GetRootNode();
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

/*
void UReadXMLLevelDetail::getMeshesToSpawn(TArray<UStaticMeshComponent*>& var)
{
	var.Reset(0);
	TArray<FString> objects;
	ReadContent[3].ParseIntoArray(objects, TEXT(","), false);
	var.SetNum(objects.Num());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, objects[0]);


	//FString Left, Right;
	//ReadContent[3].Split(TEXT("\n"), &Left, &Right);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, Right);

	//ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	//for (int i = 0; i < objects.Num(); i++) {
	//	ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectVisualAsset((TCHAR*)*objects[i]);
	//	if (ObjectVisualAsset.Succeeded()) {
	//		var[i]->SetStaticMesh(ObjectVisualAsset.Object);
	//	}
	//	
	//}
	
	//https://cpp.hotexamples.com/examples/constructorhelpers/FObjectFinder/-/cpp-fobjectfinder-class-examples.html
}
*/
void UReadXMLLevelDetail::getMeshesToSpawn(TArray<UInstancedStaticMeshComponent*>& var,AActor* root)
{
	//http://www.tomlingames.com/2017/12/simple-random-dungeon-generating-in-ue4-code/
	//https://answers.unrealengine.com/questions/819149/cooking-uinstancedstaticmeshcomponent-created-at-r.html
	TArray<FString> objects;
	ReadContent[3].ParseIntoArray(objects, TEXT(","), false);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, objects[0]);
	InstancedMeshes.Reset(0);
	InstancedMeshes.SetNum(objects.Num());
	//UStaticMesh* floor = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Meshes/Floor")));
		
	//for (int i = 0; i < InstancedMeshes.Num(); i++)
	//{
	//	UStaticMesh* floor = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, (TCHAR*)*objects[i]));
	//	InstancedMeshes[i] = NewObject<UInstancedStaticMeshComponent>(root, NAME_None, RF_NeedPostLoad);
	//	InstancedMeshes[i]->RegisterComponent();
	//	InstancedMeshes[i]->SetStaticMesh(floor);
	//	InstancedMeshes[i]->SetCollisionProfileName(TEXT("WorldStatic"));
	//	InstancedMeshes[i]->SetMobility(EComponentMobility::Static);
	//	InstancedMeshes[i]->SetFlags(RF_Transactional);
	//	InstancedMeshes[i]->AttachToComponent(root->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//	InstancedMeshes[i]->RegisterComponent();
	//	InstancedMeshes[i]->ConditionalPostLoad();
	//}

	var.Reset(0);
	var.Append(InstancedMeshes);
}