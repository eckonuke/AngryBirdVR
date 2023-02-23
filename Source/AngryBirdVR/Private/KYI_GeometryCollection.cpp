// Fill out your copyright notice in the Description page of Project Settings.


#include "KYI_GeometryCollection.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

AKYI_GeometryCollection::AKYI_GeometryCollection() {
	geometry = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Collection"));
	geometry->SetupAttachment(RootComponent);
}