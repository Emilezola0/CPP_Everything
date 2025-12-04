// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include <Components/TextRenderComponent.h>
#include "Components/SplineComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"

//GEngine AddOnScreenDebugMessage. Print function.
#include "Engine/GameEngine.h"

//ACHTUNG!! #include "X.generated.h" must ALWAYS be the last one
#include "CPP_SplineStonesRNDScales.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_SplineStonesRNDScales : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_SplineStonesRNDScales();

	//OnConstruction is called to re-build the ConstructionScript Code when a change is made. (Its replicates the behaviour of ConstructionScript in a blueprint +/-)
	virtual void OnConstruction(const FTransform& Transform) override;

	//Components Setup
	UPROPERTY()
	USceneComponent* KarimSceneRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	//Variables
	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRenderText = true;

	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones = 0;

	UPROPERTY(EditAnywhere, Category = "Default")
	float MinScale = 0.65f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float MaxScale = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZOffset = 50;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Seed = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	FRandomStream Stream;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
