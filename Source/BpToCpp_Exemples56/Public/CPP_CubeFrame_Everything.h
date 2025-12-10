// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Import Mesh
#include "Engine/StaticMesh.h"

// --------------------------------
// COMPONENTS
// --------------------------------

// Import Scene Component
#include "Components/SceneComponent.h"

// Import HISM
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Import Text Render
#include <Components/TextRenderComponent.h>

// --------------------------------
// LAST AND VERY IMPORTANT --
// --------------------------------
#include "CPP_CubeFrame_Everything.generated.h"

// --------------------------------

UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_CubeFrame_Everything : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_CubeFrame_Everything();

	// --------------------------------
	// COMPONENTS SETUP
	// --------------------------------
	
	// Scene
	UPROPERTY()
	USceneComponent* SceneRoot;

	// Text Render BP and Cube Count
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "RenderText")
	UTextRenderComponent* CubeCount;

	// HISM
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	// Static Mesh
	UPROPERTY()
	UStaticMesh* SM_Stone;

	// --------------------------------
	// CUSTOMIZABLE VARIABLES
	// --------------------------------



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
