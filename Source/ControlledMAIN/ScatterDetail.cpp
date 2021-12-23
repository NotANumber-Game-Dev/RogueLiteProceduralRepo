// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatterDetail.h"
#include "ReadXMLLevelDetail.h"


// Sets default values
AScatterDetail::AScatterDetail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScatterDetail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScatterDetail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScatterDetail::setInstancedMeshes(TArray<UInstancedStaticMeshComponent*>& var)
{
	//http://www.tomlingames.com/2017/12/simple-random-dungeon-generating-in-ue4-code/
	//https://answers.unrealengine.com/questions/819149/cooking-uinstancedstaticmeshcomponent-created-at-r.html

	UReadXMLLevelDetail::getMeshesToSpawn(instancedMeshes);

	var.Reset(0);
	var.SetNum(instancedMeshes.Num());
	//UStaticMesh* floor = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Meshes/Floor")));

	for (int i = 0; i < var.Num(); i++)
	{
		UStaticMesh* floor = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, (TCHAR*)*instancedMeshes[i]));
		var[i] = NewObject<UInstancedStaticMeshComponent>(this, NAME_None, RF_NeedPostLoad);
		var[i]->RegisterComponent();
		var[i]->SetStaticMesh(floor);
		var[i]->SetCollisionProfileName(TEXT("WorldStatic"));
		var[i]->SetMobility(EComponentMobility::Static);
		var[i]->SetFlags(RF_Transactional);
		var[i]->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		var[i]->RegisterComponent();
		var[i]->ConditionalPostLoad();
	}
}

