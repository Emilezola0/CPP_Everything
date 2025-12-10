// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// COMPONENTS
#include "Engine/StaticMesh.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include <Components/TextRenderComponent.h>
#include "Components/SceneComponent.h"


// LAST
#include "CPP_RingOfCubes.generated.h"

UENUM(BlueprintType)
enum class ERandomColor : uint8
{
	Altern				UMETA(DisplayName = "Alternative"),
	Random				UMETA(DisplayName = "Random"),
	RndSeeded			UMETA(DisplayName = "Seeded"),
	Selected			UMETA(DisplayName = "Selected"),
	AlternWithChoice	UMETA(DisplayName = "Alternate With Choice"),
};


UCLASS()
class BPTOCPP_EXEMPLES56_API ACPP_RingOfCubes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_RingOfCubes();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool ShowTextRender;

	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UHierarchicalInstancedStaticMeshComponent* HISM_00;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UTextRenderComponent* BpName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UTextRenderComponent* CubeCount;

	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMesh* SM_Stone;

	// VARIABLES
	UPROPERTY(EditAnywhere, Category = "Default")
	int CubesNUM;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Radius;

	UPROPERTY(EditAnywhere, Category = "Default")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool AutoRadius;

	UPROPERTY(EditAnywhere, Category = "Default")
	UMaterial* Material;

	UPROPERTY(EditAnywhere, Category = "Default")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, Category = "Default")
	FRandomStream Seed;

	UPROPERTY(EditAnywhere, Category = "Default")
	ERandomColor ColorGenerationType;

	UPROPERTY(EditAnywhere, Category = "Default")
	TArray<FLinearColor> AlternativeColors;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// FUNCTIONS
	UFUNCTION()
	FVector GetMeshHalfSize();

	UFUNCTION()
	void GenerateColor(int NumInstance);

};
