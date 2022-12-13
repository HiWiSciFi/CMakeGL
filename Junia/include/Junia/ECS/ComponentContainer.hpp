#pragma once

#include <unordered_map>
#include <vector>

namespace Junia
{
	namespace ECS
	{
		using EntityType = size_t;

		/**
		 * @brief A virtual container for ComponentStores
		*/
		class ComponentContainer
		{
		public:
			virtual ~ComponentContainer() = default;

			/**
			 * @brief Store a component for an entity
			 * @param e the entity to create the component for
			*/
			virtual void Insert(EntityType e) = 0;
			/**
			 * @brief Remove a component for an entity
			 * @param e the entity to remove the component for
			*/
			virtual void Erase(EntityType e) = 0;
			/**
			 * @brief Get if there is a component for an entity
			 * @param e the entity to check the component for
			 * @return true if there is a component for the entity, false
			 *              otherwise
			*/
			virtual bool HasStored(EntityType e) = 0;
			/**
			 * @brief Get all entities for which a component is stored.
			 * @param buffer The buffer to write the entities to. If this is
			 *               NULL or a nullptr nothing will be done.
			 * @return the amount of entities that have a component stored
			*/
			virtual size_t GetEntities(EntityType* buffer) = 0;
		};

		/**
		 * @brief A store for components of one type
		 * @tparam T the component type to store
		*/
		template<typename T>
		class ComponentStore : public ComponentContainer
		{
		private:
			std::vector<T> componentArray{ };
			std::unordered_map<EntityType, size_t> entityToIndexMap{ };
			std::unordered_map<size_t, EntityType> indexToEntityMap{ };

		public:
			ComponentStore() = default;

			/**
			 * @brief Store a component for an entity
			 * @param e the entity to store the component for
			 * @param component the component to store
			*/
			void Insert(EntityType e, T component)
			{
				size_t index = componentArray.size();
				componentArray.push_back(component);
				entityToIndexMap.insert({ e, index });
				indexToEntityMap.insert({ index, e });
			}

			/**
			 * @brief Store a component for an entity
			 * @param e the entity to create the component for
			*/
			virtual inline void Insert(EntityType e) override
			{
				Insert(e, T{ });
			}

			/**
			 * @brief Remove a component for an entity
			 * @param e the entity to remove the component for
			*/
			virtual inline void Erase(EntityType e) override
			{
				if (!HasStored(e)) return;
				size_t index = entityToIndexMap.at(e);
				componentArray[index] = componentArray.back();
				componentArray.pop_back();
				entityToIndexMap.erase(e);
				indexToEntityMap.erase(index);
			}

			/**
			 * @brief Get the component stored for an entity. This function
			 *        will fail if there is no component stored for the entity.
			 *        For availability checks see
			 *        ComponentContainer::HasStored()
			 * @param e the entity to get the component for
			 * @return a reference to the component stored
			*/
			inline T& Get(EntityType e)
			{
				return componentArray.at(entityToIndexMap.at(e));
			}

			/**
			 * @brief Get if there is a component for an entity
			 * @param e the entity to check the component for
			 * @return true if there is a component for the entity, false
			 *              otherwise
			*/
			virtual inline bool HasStored(EntityType e) override
			{
				return entityToIndexMap.find(e) != entityToIndexMap.end();
			}

			/**
			 * @brief Get all entities for which a component is stored.
			 * @param buffer The buffer to write the entities to. If this is
			 *               NULL or a nullptr nothing will be done.
			 * @return the amount of entities that have a component stored
			*/
			virtual inline size_t GetEntities(EntityType* buffer)
			{
				if (buffer == nullptr || buffer == NULL) return entityToIndexMap.size();
				size_t i = 0;
				for (auto const& eipair : entityToIndexMap)
				{
					buffer[i] = eipair.first;
					i++;
				}
				return entityToIndexMap.size();
			}
		};
	}
}