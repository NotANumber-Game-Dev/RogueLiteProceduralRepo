// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemyBase.generated.h"


UENUM(BlueprintType)
enum class Type : uint8 {
	Sniper  UMETA(DisplayName = "Francotirador"),
	Melee UMETA(DisplayName = "Cuerpo a cuerpo"),
	MidRange UMETA(DisplayName = "Fusiles"),
};

//Primeras armes seran cos a cos - seguents seran fusils  i per ultim snipers
UENUM(BlueprintType)
// qui mogui les armes de lloc el mato
enum class Weapon : uint8 {
	Pistol  UMETA(DisplayName = "Pistola"),
	Katana UMETA(DisplayName = "Katana"),
	M4a1 UMETA(DisplayName = "M4a1"),
};

UCLASS()
class CONTROLLEDMAIN_API ACEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemyBase();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyLists")
		Type EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyLists")
		Weapon EnemyWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "EnemyStats")
		int HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
		int Accuracy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
		int VisionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
		int SoundRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyStats")
		bool Granade;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	
	




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
