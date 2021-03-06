// Copyright (c) 2012-2020 Wojciech Figat. All rights reserved.

#pragma once

#include "../BinaryAsset.h"
#include "Engine/Animations/Graph/AnimGraph.h"

/// <summary>
/// The Animation Graph is used to evaluate a final pose for the animated model for the current frame.
/// </summary>
API_CLASS(NoSpawn) class FLAXENGINE_API AnimationGraph : public BinaryAsset
{
DECLARE_BINARY_ASSET_HEADER(AnimationGraph, 1);

public:

    /// <summary>
    /// The animation graph.
    /// </summary>
    AnimGraph Graph;

    /// <summary>
    /// The animation graph runtime executor.
    /// </summary>
    AnimGraphExecutor GraphExecutor;

public:

    /// <summary>
    /// Gets the base model asset used for the animation preview and the skeleton layout source.
    /// </summary>
    /// <returns>The base model.</returns>
    API_PROPERTY() SkinnedModel* GetBaseModel() const
    {
        return Graph.BaseModel.Get();
    }

    /// <summary>
    /// Tries to load surface graph from the asset.
    /// </summary>
    /// <returns>The surface data or empty if failed to load it.</returns>
    API_FUNCTION() BytesContainer LoadSurface();

#if USE_EDITOR

    /// <summary>
    /// Updates the animation graph surface (save new one, discard cached data, reload asset).
    /// </summary>
    /// <param name="data">Stream with graph data.</param>
    /// <returns>True if cannot save it, otherwise false.</returns>
    API_FUNCTION() bool SaveSurface(BytesContainer& data);

private:

    void FindDependencies(AnimGraphBase* graph);

#endif

public:

    // [BinaryAsset]
#if USE_EDITOR
    void GetReferences(Array<Guid>& output) const override
    {
        // Base
        BinaryAsset::GetReferences(output);

        Graph.GetReferences(output);
    }
#endif

protected:

    // [BinaryAsset]
    LoadResult load() override;
    void unload(bool isReloading) override;
    AssetChunksFlag getChunksToPreload() const override;
#if USE_EDITOR
    void OnDependencyModified(BinaryAsset* asset) override;
#endif
};
