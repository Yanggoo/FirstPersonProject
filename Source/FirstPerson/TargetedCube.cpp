// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetedCube.h"
#include "FirstPersonGameMode.h"
#include "FirstPersonGameState.h"
#include "FirstPersonPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "FirstPersonPlayerState.h"

// Sets default values
ATargetedCube::ATargetedCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsImportantCube = false;
	bReplicates = true;

	//Create static mesh component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube"));
	if (CubeMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(CubeMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ChamferCubeMaterial(
		TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Blue"));
	if (ChamferCubeMaterial.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, ChamferCubeMaterial.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(
		TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Yellow"));
	if (Material.Succeeded())
	{
		MaterialOfImportantCube = Material.Object;
	}
	else
	{
		MaterialOfImportantCube = nullptr;
	}

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void ATargetedCube::BeginPlay()
{
	Super::BeginPlay();
	HitNum = 0;
}

void ATargetedCube::OnRep_IsImportant()
{
	StaticMeshComponent->SetMaterial(0, MaterialOfImportantCube);
}

// Called every frame
void ATargetedCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATargetedCube::SetImportant()
{
	IsImportantCube = true;
	StaticMeshComponent->SetMaterial(0, MaterialOfImportantCube);
}

void ATargetedCube::HandleHit(AActor* owner)
{
	AFirstPersonGameState* GameState = GetWorld()->GetGameState<AFirstPersonGameState>();
	checkf(GameState, TEXT("No available game state"));
	if (HitNum == 0)
	{
		HitNum++;
		FVector currentScale = StaticMeshComponent->GetComponentScale();
		StaticMeshComponent->SetWorldScale3D(GameState->GetYScale() * currentScale);
	}
	else
	{
		if (AFirstPersonPlayerController* pFirstPersonPlayerController = Cast<AFirstPersonPlayerController>(owner))
		{
			if (HasAuthority())
			{
				if (IsImportant())
				{
					pFirstPersonPlayerController->AddScore(GameState->GetXPoints() * 2);
				}
				else
				{
					pFirstPersonPlayerController->AddScore(GameState->GetXPoints());
				}

				if(AFirstPersonPlayerController* PlayerController = Cast<AFirstPersonPlayerController>(owner))
				{
					PlayerController->GetPlayerState<AFirstPersonPlayerState>()->PlayerScoreUpdateDelegate.Broadcast();
				}
			}

			Destroy();
		}
	}
}

void ATargetedCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATargetedCube, IsImportantCube);
}
