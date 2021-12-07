// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyBase.h"

// Sets default values
ACEnemyBase::ACEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HP = 0;
	Accuracy = 0;
	VisionRange = 0;
	SoundRange = 0;
	Granade = false;
	EnemyType = Type::Melee;
	EnemyWeapon = Weapon::Katana;

}

// Called when the game starts or when spawned
void ACEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

