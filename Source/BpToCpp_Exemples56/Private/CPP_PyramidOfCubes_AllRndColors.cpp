// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PyramidOfCubes_AllRndColors.h"

// import Math
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ACPP_PyramidOfCubes_AllRndColors::ACPP_PyramidOfCubes_AllRndColors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components Setup
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	RootComponent = SceneRoot;

	BpName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name of the Bp"));
	BpName->SetupAttachment(SceneRoot);

	CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Total Cubes"));
	CubeCount->SetupAttachment(SceneRoot);

	HISM_00 = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("MainHISM"));
	HISM_00->SetupAttachment(SceneRoot);

	//Default Values
	bRenderText = true;
	Stones_Z = 0;
	StoneZOffset = 50.0f;

}

void ACPP_PyramidOfCubes_AllRndColors::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Setup
	BpName->SetVisibility(bRenderText);
	CubeCount->SetVisibility(bRenderText);
	HISM_00->ClearInstances();
	HISM_00->SetStaticMesh(SM_Stone);

	// Setup Colors for HISM
	HISM_00->NumCustomDataFloats = 3;
	FLinearColor L_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// If valid conditions
	if (Stones_Z >= 1 && SM_Stone && Material)
	{
		// TO DO Setup Visibility
		// Setup
		HISM_00->SetMaterial(0, Material);
		FVector L_StoneLocation;
		FRotator L_StoneRotation;
		FVector L_StoneScale;
		FTransform L_InstanceTransform;
		int L_InstanceIndex;

		int i = 0;
		// Height
		for (i = 0; i < Stones_Z + 1; i++)
		{
			// Floor
			int j = i;
			int k = i;
			for (j = 0; j < i; j++) 
			{
				for (k = 0; k < i; k++)
				{
					float L_ZLocOffsetForX = GetStaticMeshSize(SM_Stone).X * (((Stones_Z) - float(i)) / 2) * -1;
					float L_ZLocOffsetForY = GetStaticMeshSize(SM_Stone).Y * (((Stones_Z) - float(i)) / 2) * -1;

					float L_XLoc = (GetStaticMeshSize(SM_Stone).X * float(j)) - L_ZLocOffsetForX;
					float L_YLoc = (GetStaticMeshSize(SM_Stone).Y * float(k)) - L_ZLocOffsetForY;
					float L_ZLoc = StoneZOffset + (GetStaticMeshSize(SM_Stone).Z * ((Stones_Z) - float(i)));

					// Set Transform
					L_StoneLocation = FVector(L_XLoc, L_YLoc, L_ZLoc);
					L_StoneRotation = { 0, 0, 0 };
					L_StoneScale = { 1.0f,1.0f,1.0f };
					L_InstanceTransform = FTransform(
						FRotator::ZeroRotator,
						FVector(L_XLoc, L_YLoc, L_ZLoc),
						FVector(1.0f, 1.0f, 1.0f)
					);

					L_InstanceIndex = HISM_00->AddInstance(L_InstanceTransform, false);
					UKismetMathLibrary::LinearColor_SetRandomHue(L_Color);

					HISM_00->SetCustomDataValue(L_InstanceIndex, 0, L_Color.R, false);
					HISM_00->SetCustomDataValue(L_InstanceIndex, 1, L_Color.G, false);
					HISM_00->SetCustomDataValue(L_InstanceIndex, 2, L_Color.B, false);
				}
			}
		}
	}

	// Texts
	FString Str = "Cube Count : ";
	Str.AppendInt(HISM_00->GetInstanceCount());
	CubeCount->SetText(FText::FromString(Str));
	// If I want the display name
	FString DisplayName = GetClass()->GetDefaultObject()->GetName();
	// Exemple BpName->SetText(FText::FromString(DisplayName));
	BpName->SetText(FText::FromString("BP_PyarmidOfCubes_AllRndColors"));
	
	// Set Texts Locations
	float HalfSize = GetStaticMeshSize(SM_Stone).X / 2;
	float L_TextLocX = (((Stones_Z * GetStaticMeshSize(SM_Stone).X)) / 2) - HalfSize;
	float L_TextLocY = (((Stones_Z * GetStaticMeshSize(SM_Stone).Y)) / 2) - HalfSize;
	float L_TextLocZ = StoneZOffset + (Stones_Z * GetStaticMeshSize(SM_Stone).Z);
	BpName->SetRelativeLocation(FVector(L_TextLocX, L_TextLocY, L_TextLocZ + 25));
	CubeCount->SetRelativeLocation(FVector(L_TextLocX, L_TextLocY, L_TextLocZ));;
	// Set Texts Alignements
	BpName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	BpName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	CubeCount->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	CubeCount->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);

}

// Called when the game starts or when spawned
void ACPP_PyramidOfCubes_AllRndColors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_PyramidOfCubes_AllRndColors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACPP_PyramidOfCubes_AllRndColors::GetStaticMeshSize(class UStaticMesh* Mesh)
{
	if (!Mesh)
		return FVector::ZeroVector;


	return Mesh->GetBounds().GetBox().GetSize();
}

