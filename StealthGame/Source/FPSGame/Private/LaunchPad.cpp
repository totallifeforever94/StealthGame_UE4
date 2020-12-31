// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPad.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	OverlappingComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappingComp"));
	OverlappingComp->SetupAttachment(MeshComp);

	LaunchPitchAngle = 35.f;
	LaunchStrength = 1500.f;
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALaunchPad::NotifyActorBeginOverlap(AActor *OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);


	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter *OtherCharacter = Cast<ACharacter>(OtherActor);
	UPrimitiveComponent *PrimitiveComp = Cast<UPrimitiveComponent>(OtherActor);

	if (OtherCharacter)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
	else if (PrimitiveComp && PrimitiveComp->IsSimulatingPhysics())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
		PrimitiveComp->AddImpulse(LaunchVelocity, NAME_None, true);
	}
}
