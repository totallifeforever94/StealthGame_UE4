// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComponent->DecalSize = FVector(200.f);
	DecalComponent->SetupAttachment(OverlapComp);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlaped with extraction zone"));

	AFPSCharacter *PlayerCharacter = Cast<AFPSCharacter>(OtherActor);

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	if (PlayerCharacter->bIsCarryingObjective)
	{
		AFPSGameMode *GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->CompleteMission(PlayerCharacter, true);
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ObjectiveMissingSound, PlayerCharacter->GetActorLocation());
	}
}
