
# super-nlp-ue4

A plugin for Unreal Engine 4, leveraging Tensorflow for natural language processing capabilities.

This plugin was developed using [getnamo's tensorflow-ue4 plugin](https://github.com/getnamo/tensorflow-ue4), which you can access here.

This plugin lets you extract entities and intents from sentences fully in Blueprints, without the need to code in C++ or Python!

## Installation

1.  To use this NLP plugin, you must first follow the instructions for intalling [tensorflow-ue4](https://github.com/getnamo/tensorflow-ue4/releases).
2.    Download and add [super-nlp-ue4 plugin](https://github.com/datasauces/super-nlp-ue4) to \Plugins
3.    Download and add [GoogleNews-vectors-negative300.bin (3.39 GB!)](https://drive.google.com/file/d/0B7XkCwpI5KDYNlNUTTlSS21pQmM/edit?usp=sharing) to \Content\Scripts

## Examples

You can find a simplistic example project here:

https://github.com/datasauces/super-nlp-ue4-examples

For a more detailed use of this plugin, you can find a text-based adventure game we've been working on here:

https://github.com/datasauces/super-nlp-puzzlegame

## Feature Overview

This Plugin's workings were heavily inspired by [Microsoft LUIS](https://eu.luis.ai). Similarly to it, we work with entities and intents. The main difference between LUIS and this plugin is that this plugin operates offline, thus eliminating the need to pay Microsoft Azure, but it currently lacks a few features that Microsoft LUIS provides, such as patterns, regexes, etc. We aspire to implement these features later on.

For a clear understanding of how to use this plugin, there are two major parts: an in-engine part and an out-of-engine part. Let's begin with the latter.

### Out-of-engine

#### Entities

Navigate to \Content\Entities.

In this folder, you can create as many entities as you wish. Each type of entity must be a .csv file, and the filename will represent the type of the entity.

The .csv file must have the following structure:

[Entity Image]

1. Field A1 must be empty or contain "---"
2. Field B1 must contain "Entities"
3. Field A2 must contain either True or False. This determines whether the entity has an impact on the intent of a sentence, i.e., if the entity is significant. Colors and many adjectives may be considered insignificant as far as the intent is concerned. True = significant, False = insignificant
4. Field B2, B3, B4 and so on have to be structured as seen in the image. Words that fall within the same entity/category but have different meanings should be in separate fields, while synonyms should be in the same field. (For instance, Red and Ruby are in the same field, since, in our case, they're synonyms, whereas blue is in a different field.)
5. Field A3, A4, A5 and so on must have unique names, but the names are irrelevant, so you can simply use row numbers for simplicity.

The first word in B2 will be referred to as the "base" of that Entity from here on.

#### TrainingData and Intents

Navigate to \Content\Scripts.

This folder must contain 3 .csv files for the plugin to function:

    TrainingDataSentences.csv

    TrainingDataIntents.csv

    Intents.csv

The following screenshot shows those files open in that order, from left to right: TrainingDataSentences, TrainingDataIntents, and Intents.

[Intents Image]

So, what's happening here?
TrainingDataSentences.csv (left-hand file) includes the sentences our neural net will be training on for intent recognition.
This should contain sentences similar to what players may be entering in the game. However, there's a very strict way to structure them.

1. Change sentences to lowercase.
2. Eliminate all punctuation marks (,.?!)
3. Remove all stop words:

    The given list of stop words

4. Make sure you replace all words that belong to an Entity with the base of that entity (see Entities)
5. If a word belongs to an entity that is deemed insignificant to the intent, remove it.

So, for instance, let's assume we have:

    an Entity of Objects with base barrel
    an Entity of Colors with base red, and is set to be insignificant
    an Intent of Equipables with base key
    
We would want to add the following sentence to our training set:

    Open the green chest using the blue key!
   
After the above structuring, it would become: 

    open barrel using key

This sentence can then be added to our .csv file, where each word is a separate field, and all the remaining fields, after the sentence is complete, are filled with "none" until J. (a maximum of 10 words)

Of course, this sentence corresponds to an intent. We must select the corresponding intent for this sentence. We do this in TrainingDataIntents.csv, where we set the corresponding field to 1, and all incorrect fields to 0. 

These columns correspond directly with the rows in Intents.csv. So, for example, if Intents.csv has the following fields: B2:GoTo, B3:GoThrough, B4:Use and B5:PickUp.

The first of these, GoTo, corresponds to the first column in TrainingDataIntents.csv, the second one, GoThrough, corresponds to the second column, and so on. 

Intents.csv has similar rules to Entities;

1. Field A1 must be empty or contain "---"
2. Field B1 must contain "Intents" (!!!)
3. Field A3, A4, A5 and onwards must have unique names, but the names are irrelevant, so you can simply use row numbers for simplicity.

### In-engine

To use natural language processing in a blueprint, you need to add a TensorflowComponent and a NaturalLanguageComponent.

[TensorFlow Image]

Set the TensorFlowModule in the TensorflowComponent to "GlennvWsNaturalLanguageProcessing"

[TensorFlowModule Image]

Set the Intent Data Table in the NaturalLanguageComponent to your data table containing your intents. (There should be one by default, which you can modify as per your needs)

Next, all you have to do to use language processing is the following:

[Sentence Process Image]

Anywhere in your code, where you intend to process a sentence, call "Process Sentence" from the NaturalLanguageComponent and pass your sentence (string).

On Beginplay bind an event to SentenceProcessed from the NaturalLanguageComponent. This event will be called when the net finishes processing after you call "Process Sentence", receiving the Intent (String) and the Detected Entities (Array of Entity Type (String) and Specific Entity (String) in the order that they appeared in the original sentence). You can parse this result as you wish.

### Video Overview

That may sound overwhelming, so you can also watch this video for a quick summary of the plugin's features!

[INSERT VIDEO HERE]

## Troubleshooting

### command window pops up on first begin play

On first play, the plugin adds modules to the python virtual environment. This may take a few minutes depending on internet connectivity. 

### the NaturalLanguageComponent does not complete training
Wait for a few minutes before pressing play again. Python modules are being installed in the background, just be patient!

## [License](https://github.com/datasauces/super-nlp-ue4/blob/master/LICENSE)
NLP and Tensorflow Plugin - [MIT](https://opensource.org/licenses/MIT)

TensorFlow and TensorFlow Icon - [Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0)