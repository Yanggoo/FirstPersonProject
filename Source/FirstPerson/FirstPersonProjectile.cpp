// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonProjectile.h"

#include "FirstPersonCharacter.h"
#include "FirstPersonPlayerController.h"
#include "FirstPersonPlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TargetedCube.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/IHttpResponse.h"

AFirstPersonProjectile::AFirstPersonProjectile() 
{
	bReplicates = true;
	bAlwaysRelevant = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFirstPersonProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	Damage = 10.0f;
	
}

void AFirstPersonProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
		if (ATargetedCube* HitCube = Cast<ATargetedCube>(OtherActor))
		{
			if(OtherComp->IsSimulatingPhysics())
			{
				OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
				HitCube->HandleHit(Owner);
			}
		}else if(AFirstPersonCharacter* HitPlayer = Cast<AFirstPersonCharacter>(OtherActor))
		{
			if(HasAuthority())
			{
				AFirstPersonPlayerState* PlayerState = Cast<AFirstPersonPlayerState>(HitPlayer->GetPlayerState());
				if(PlayerState)
				{
					PlayerState->TakeDamage(Damage);
				}
			}
			if(AFirstPersonPlayerController* PlayerController = Cast<AFirstPersonPlayerController>(Owner))
			{
				PlayerController->CrosshairUpdate.Broadcast();
			}
		}
		Destroy();
	}
}