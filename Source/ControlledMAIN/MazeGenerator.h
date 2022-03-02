// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"


UENUM()
enum FBioma
{
	none UMETA(DisplayName = "none"),
	Bottom_Sewer UMETA(DisplayName = "Bottom Sewer"),
	High_Sewer UMETA(DisplayName = "High Sewer"),
	City_Suburb UMETA(DisplayName = "City Suburb"),
	Fabric_Armament UMETA(DisplayName = "Fabric Armament"),
	Fabric_BIOS UMETA(DisplayName = "Fabric BIOS"),
	City_Mainstreet UMETA(DisplayName = "City Mainstreet"),
	BluBuilding_Hall UMETA(DisplayName = "Blu Building Hall"),
	BluBuilding_Middlefloor UMETA(DisplayName = "Blu Building Middle floor"),
	BluBuilding_Penthouse UMETA(DisplayName = "Blu Building Penthouse")
};

USTRUCT()
struct FNestetdArray {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, category = "Load Maps")
		TArray<int>A;
		
};

USTRUCT()
struct FPos {
	GENERATED_BODY()
		UPROPERTY()
		int X;
	UPROPERTY()
		int Y;
};

UCLASS()
class CONTROLLEDMAIN_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();
	//UPROPERTY(EditAnywhere, category = "Load Maps")
		TArray<FString> nameMaps;



	//Check the number before, probably scale*100
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Load Maps")
		int sizeSquare;

	//How many squares you want
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Load Maps")
		int SIZE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Load Maps")
		TEnumAsByte<FBioma> biomes;

	UFUNCTION(BlueprintPure)
		FVector getBossPosition();

	UFUNCTION(BlueprintPure)
		int getSizeSquare();

	UFUNCTION(BlueprintCallable)
		void setBiomes(FString bioma);

	UFUNCTION(BlueprintCallable)
		void getRoomOrentation(float _x, float _y, int &id_sala, int &posX_in_maze, int& posY_in_maze);

	UFUNCTION(BlueprintCallable)
		void getRoomOrentationWithXY(int _x, int _y, int& id_sala);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Load Maps")
		FVector playerStart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FNestetdArray> _maze;

	FVector boss;
	
	int _posCount;
	FPos _currentPos;
	TArray<FPos> _prevPosList;
	int _randNum;
	bool _randPrev[4];

	int _checkedPos;

	void generator();
	int getRandomDirection();
	void addToCount(int i);
	void canContinue(int x, int y);


	TArray<FString> XMLContent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	void init();
	void RenderLevels();
	bool isWalOnPos(int x, int y);
};
