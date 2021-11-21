// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

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
	UPROPERTY(EditAnywhere, category = "Load Maps")
		TArray<FString> nameMaps;

	UPROPERTY(EditAnywhere, category = "Load Maps")
		int sizeSquare;
	UPROPERTY(EditAnywhere, category = "Load Maps")
		int SIZE;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FNestetdArray> _maze;


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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void init();
	bool isWalOnPos(int x, int y);
};
