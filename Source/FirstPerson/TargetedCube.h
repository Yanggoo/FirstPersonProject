// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetedCube.generated.h"

UCLASS()
class FIRSTPERSON_API ATargetedCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATargetedCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* MaterialOfImportantCube;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(ReplicatedUsing=OnRep_IsImportant)
	bool IsImportantCube;
	int32 HitNum;
	UFUNCTION()
	void OnRep_IsImportant();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetImportant();
	inline bool IsImportant() const { return IsImportantCube; }
	void HandleHit(AActor* owner);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
