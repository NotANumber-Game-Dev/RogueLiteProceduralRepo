// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScatterDetail.generated.h"

UCLASS()
class CONTROLLEDMAIN_API AScatterDetail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScatterDetail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FString> instancedMeshes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//AQUI HE DE FER LA LECTURA I CREAR INSTANCEDMESHES

	UFUNCTION(BlueprintCallable, Category = "Test")
	void setInstancedMeshes(TArray<UInstancedStaticMeshComponent*>& var);
};
