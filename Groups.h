#pragma once

#include <string>
#include <vector>
#include <any>
#include <memory>

/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё 
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */


namespace TopoR_PCB_Classes
{
	/// <summary>
	/// Раздел «Группировка объектов».
	/// </summary>
	class Groups : public std::enable_shared_from_this<Groups>
	{
		/// <summary>
		/// Описание групп слоёв.
		/// </summary>
	public:
		class LayerGroup : public std::enable_shared_from_this<LayerGroup>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Ссылка на слой или ссылка на группу слоёв.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("LayerRef", typeof(LayerRef)), XmlElement("LayerGroupRef", typeof(LayerGroupRef))] public List<Object> _LayerRefs;
			std::vector<std::any> _LayerRefs;
			bool ShouldSerialize_LayerRefs();
			/**********************************************************************
			 * Здесь находятся функции для работы с элементами класса LayerGroup. *
			 * Они не являются частью формата TopoR PCB.                          *
			 * *******************************************************************/
			std::wstring ToString();
			/*********************************************************************/
		};

		/// <summary>
		/// Описание группы цепей.
		/// </summary>
	public:
		class NetGroup : public std::enable_shared_from_this<NetGroup>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Ссылка на цепь или ссылка на группу цепей.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("NetRef", typeof(NetRef)), XmlElement("NetGroupRef", typeof(NetGroupRef))] public List<Object> _NetRefs;
			std::vector<std::any> _NetRefs;
			bool ShouldSerialize_NetRefs();
		};

		/// <summary>
		/// Описание группы компонентов.
		/// </summary>
	public:
		class CompGroup : public std::enable_shared_from_this<CompGroup>
		{
			/// <summary>
			/// Имя объекта или ссылка на именованный объект.
			/// </summary>
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("name")] public string _name;
			std::wstring _name;

			/// <summary>
			/// Ссылка на компонент на плате или ссылка на группу компонентов.
			/// </summary>
//C# TO C++ CONVERTER TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlElement("CompInstanceRef", typeof(CompInstanceRef)), XmlElement("CompGroupRef", typeof(CompGroupRef))] public List<Object> _CompRefs;
			std::vector<std::any> _CompRefs;
			bool ShouldSerialize_CompRefs();
		};

		/// <summary>
		/// Версия раздела.
		/// </summary>
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlAttribute("version")] public string _version;
		std::wstring _version;

		/// <summary>
		/// Группы слоёв.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("LayerGroups")][XmlArrayItem("LayerGroup")] public List<LayerGroup> _LayerGroups;
		std::vector<std::shared_ptr<LayerGroup>> _LayerGroups;
		bool ShouldSerialize_LayerGroups();
		/// <summary>
		/// Группы цепей.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("NetGroups")][XmlArrayItem("NetGroup")] public List<NetGroup> _NetGroups;
		std::vector<std::shared_ptr<NetGroup>> _NetGroups;
		bool ShouldSerialize_NetGroups();
		/// <summary>
		/// Группы компонентов.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [XmlArray("CompGroups")][XmlArrayItem("CompGroup")] public List<CompGroup> _CompGroups;
		std::vector<std::shared_ptr<CompGroup>> _CompGroups;
		bool ShouldSerialize_CompGroups();

		/******************************************************************
		 * Здесь находятся функции для работы с элементами класса Groups. *
		 * Они не являются частью формата TopoR PCB.                      *
		 * ****************************************************************/

		/// <summary>
		/// Переименование ссылок на компонент, если его имя изменилось
		/// </summary>
		/// <param name="oldname">старое имя компонента</param>
		/// <param name="newname">новое имя компонента</param>
		void Rename_compName(const std::wstring &oldname, const std::wstring &newname);
		/******************************************************************/
	};
}
