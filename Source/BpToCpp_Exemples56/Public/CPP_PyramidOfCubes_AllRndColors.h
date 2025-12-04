// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Import Scene, Text, Static Mesh, and HISM
#include "Components/SceneComponent.h"
#include <Components/TextRenderComponent.h>
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Last
#include "CPP_PyramidOfCubes_AllRndColors.generated.h"

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_PyramidOfCubes_AllRndColors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PyramidOfCubes_AllRndColors();

	//OnConstruction is called to re-build the ConstructionScript Code when a change is made. (Its replicates the natural behaviour of a blueprint)
	virtual void OnConstruction(const FTransform& Transform) override;
	
	//Components Setup
	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	// Variables Setup
	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones_Z;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRenderText;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZOffset;

	UPROPERTY(EditAnywhere, Category = "Default")
	UMaterialInterface* Material;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Functions
	UFUNCTION()
	static FVector GetStaticMeshSize(class UStaticMesh* Mesh);

};
