// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// ---------------------------
// COMPONENTS
// ---------------------------

// Scene Components
#include "Components/SceneComponent.h"

// Text Render
#include <Components/TextRenderComponent.h>

// HISM
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Static Mesh
#include "Engine/StaticMesh.h"

// ---------------------------
// LAST
// ---------------------------
#include "CPP_CubeFrame.generated.h"

/*
---
*/
// Enum for Random stuff
UENUM(BlueprintType)
enum class ETypeOfRnd : uint8
{
	None				UMETA(DisplayName = "None"),
	Random				UMETA(DisplayName = "Random"),
	Seeded				UMETA(DisplayName = "Seeded"),
	SeededUniformColor	UMETA(DisplayName = "Seeded Uniform Color"),
	Selected			UMETA(DisplayName = "From Selection"),
};

// Enum for Mesh Scaleability
UENUM(BlueprintType)
enum class ETypeOfSize : uint8
{
	Default				UMETA(DisplayName = "Default Size"),
	FullRandom			UMETA(DisplayName = "Random"),
	Seeded				UMETA(DisplayName = "Seeded"),
	SeededUniform		UMETA(DisplayName = "Seeded Uniform Size"),
	Selected			UMETA(DisplayName = "Selected"),
};


UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_CubeFrame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_CubeFrame();

	//OnConstruction is called to re-build the ConstructionScript Code when a change is made. (Its replicates the natural behaviour of a blueprint)
	virtual void OnConstruction(const FTransform& Transform) override;

	// ---------------------------
	// COMPONENTS VARIABLES
	// ---------------------------

	// SCENE COMPONENT
	UPROPERTY()
	USceneComponent* SceneRoot;

	// TEXT RENDER
	UPROPERTY()
	UTextRenderComponent* BpName;

	UPROPERTY()
	UTextRenderComponent* CubeCount;


	// HISM
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	// MESH
	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	// Colors
	UPROPERTY(EditAnywhere, Category = "Default")
	FLinearColor MeshColor;


	// ---------------------------
	// VARIABLES
	// ---------------------------

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones_X;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones_Y;

	UPROPERTY(EditAnywhere, Category = "Default")
	int Stones_Z;

	UPROPERTY(EditAnywhere, Category = "Default")
	float StoneZ_Offset;

	UPROPERTY(EditAnywhere, Category = "Default")
	UMaterial* Material;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRenderText;

	// OTHERS CONDITIONS FOR DIFFERENTS USAGES
	UPROPERTY(EditAnywhere, Category = "Parameters|Color")
	ETypeOfRnd RandomGenerationTypeOfColor;

	// SEED
	UPROPERTY(EditAnywhere, Category = "Parameters|Color")
	int32 ColorSeedValue;

	UPROPERTY(EditAnywhere, Category = "Parameters|Color")
	FRandomStream ColorRandomStream;

	// ---------------------------
	// Bonus Variables
	// ---------------------------

	UPROPERTY(EditAnywhere, Category = "Parameters|Size")
	ETypeOfSize TypeOfMeshSizeGeneration;

	UPROPERTY(EditAnywhere, Category = "Parameters|Size|Selected")
	FVector MeshSize;

	UPROPERTY(EditAnywhere, Category = "Parameters|Size|Random")
	float MeshMinSize;

	UPROPERTY(EditAnywhere, Category = "Parameters|Size|Random")
	float MeshMaxSize;

	// SEED
	UPROPERTY(EditAnywhere, Category = "Parameters|Size|Random")
	int32 SizeSeedValue;

	UPROPERTY(EditAnywhere, Category = "Parameters|Size|Random")
	FRandomStream SizeRandomStream;

	UPROPERTY(VisibleDefaultsOnly, Category = "Parameters|Size|Private")
	FVector MeshSizeMemory;


	// UENUM(BlueprintType) Rend l'enum accessible et utilisable dans les Blueprints

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CubeFrameCondition(int Index, int Stone);

	// Return the Half Size of the mesh
	FVector GetMeshHalfSize();

	// Use this for ENUM and all conditions
	void SetupMeshSize();

};
