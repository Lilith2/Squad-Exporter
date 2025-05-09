# Squad-Exporter

**Squad-Exporter** is a Notepad++ plugin designed to convert specific C++ class and struct formats into clean, readable C# code. This is especially useful for projects that rely on memory structures and offset mapping from C++ games into managed C# environments.

## 📦 What It Does

Squad-Exporter reads structures or class definitions generated by [Dumper7](https://github.com/Encryqed/Dumper-7) and extracts field data into your specified C# format — preserving field names and original types for easy reference and accurate code translation. It will of coures translate the offsets from the comments into uint values on your C# fields.

It helps you avoid cryptic values in your C# code, ensuring the resulting structs remain human-readable and aligned with the C++ source.

## 📁 Input Files

You must use the following four files as input, generated by Dumper7:

- `Game_classes.hpp`
- `Game_structs.hpp`
- `Engine_classes.hpp`
- `Engine_structs.hpp`

> 🔁 Replace `Game` with the name of the game you're working on. List of files located in function getOpenHPPFiles in the file PluginDefinition.cpp

## 📝 Output File Setup

Before running Squad-Exporter, you need to create and prepare a file named `Offsets.cs`. This file must follow a specific structure so the tool knows what C++ classes/structs to look for and convert.

### Format Example

```csharp
namespace Offsets
{
    public struct FSQSwayData
    {
    }
}
