// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// COMPONENTS
#include "Components/SceneComponent.h"
#include <Components/TextRenderComponent.h>
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

#include "Components/SplineComponent.h"

#include "Engine/StaticMesh.h"

// LAST
#include "CPP_AllSplinesStones.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_AllSplinesStones : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_AllSplinesStones();

	virtual void OnConstruction(const FTransform& Transform) override;

	// COMPONENTS
	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;

	// VARIABLES
	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Stones_Z;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZ_Offset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// FUNCTION
	UFUNCTION()
	FVector GetMeshHalfSize();

};
