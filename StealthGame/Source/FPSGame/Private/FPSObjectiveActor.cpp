// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SpehereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SpehereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpehereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpehereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SpehereComp->SetupAttachment(MeshComp);
}


// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSObjectiveActor::PlayEffects() 
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor *OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();
}

