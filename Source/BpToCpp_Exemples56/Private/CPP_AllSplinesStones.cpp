// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AllSplinesStones.h"

// Sets default values
ACPP_AllSplinesStones::ACPP_AllSplinesStones()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ADD COMPONENTS
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	
	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BpName"));
	BpName->SetupAttachment(SceneRoot);
	
	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("^CubeCount"));
	CubeCount->SetupAttachment(SceneRoot);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(SceneRoot);

	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM_00"));
	HISM_00->SetupAttachment(SceneRoot);

	// Set Default In Editor
	StoneZ_Offset = 50.f;

}

void ACPP_AllSplinesStones::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// CLEAR INSTANCE
	HISM_00->ClearInstances();

	// LOCAL VAR
	FVector L_SplineLoc;
	FRotator L_SplineRot;

	if (SM_Stone && Stones_Z > 0)
	{
		// SET STATIC MESH
		HISM_00->SetStaticMesh(SM_Stone);

		// GET LENGTH AND GET NUMBER OF LOOP TO DO
		float Length = Spline->GetSplineLength();
		int NumOfLoop = Length / (GetMeshHalfSize().Y * 2);

		int l = 0;
		int i = 0;
		for (l = 0; l < NumOfLoop; l++)
		{
			L_SplineLoc = Spline->GetLocationAtDistanceAlongSpline(l * GetMeshHalfSize().X * 2, ESplineCoordinateSpace::Local) + FVector(0.f, 0.f, StoneZ_Offset);
			L_SplineRot = Spline->GetRotationAtDistanceAlongSpline(l * GetMeshHalfSize().X * 2, ESplineCoordinateSpace::Local);
			
			i = 0;
			for (i = 0; i < Stones_Z; i++)
			{

				HISM_00->AddInstance(FTransform(
					L_SplineRot,
					L_SplineLoc + FVector(0.f, 0.f, i * GetMeshHalfSize().Z * 2),
					FVector(1.f, 1.f, 1.f)
				));
			}
		}
	}

}

// Called when the game starts or when spawned
void ACPP_AllSplinesStones::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_AllSplinesStones::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACPP_AllSplinesStones::GetMeshHalfSize()
{
	return SM_Stone->GetBounds().GetBox().GetExtent();
}