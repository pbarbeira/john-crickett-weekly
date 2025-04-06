//
// Created by pbarbeira on 05-04-2025.
//

#ifndef HUFFMANENGINE_H
#define HUFFMANENGINE_H

#include <codecvt>
#include <string>

#include "encoder/CharCounter.h"
#include "encoder/Decoder.h"
#include "encoder/Encoder.h"
#include "utils/Reader.h"
#include "utils/Writer.h"

/**
 * Pure virtual class. Used to encapsulate Encode and Decode behaviors.
 */
class HuffmanEngine{
    public:
    /**
     * Default virtual destructor.
     */
    virtual ~HuffmanEngine() = default;

    /**
     * Pure virtual function to be implemented by the Encode and Decode Engines.
     * Receives a path to an input file and a path to an output file.
     * @param inputFile the path to the input file.
     * @param outputFile the path to the output file.
     */
    virtual void run(const std::string& inputFile, const std::string& outputFile) = 0;
};

/**
 * Encode Engine API. Encapsulates the encoding process.
 */
class HuffmanEncodeEngine final : public HuffmanEngine{
    public:
        /**
         * Takes an input file and compresses it into an ouput file using
         * HuffmanEnconding.
         * @param inputFile the path to the input file.
         * @param outputFile the path to the output file.
         */
        void run(const std::string& inputFile, const std::string& outputFile) override{
            const std::string text = HmcReader::readAsString(inputFile);

            if (text.empty()) {
                throw std::runtime_error("Input file is empty");
            }

            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            const std::wstring wText = converter.from_bytes(text);

            const auto frequencyMap = CharCounter::countChars(wText);
            const auto root = HuffmanTree::buildTree(frequencyMap);

            const auto header = HuffmanTree::encodeHeader(root.get());
            HmcWriter::writeHeader(outputFile, header);

            const auto encoder = Encoder(root.get());
            const auto body = encoder.encode(wText);
            HmcWriter::writeBody(outputFile, body);

            std::cout << std::format("File saved at {}", outputFile) << std::endl;
        };
};

/**
 * Decode Engine API. Encapsulates the decoding process.
 */
class HuffmanDecodeEngine final : public HuffmanEngine{
    public:
        /**
         * Takes an input file compressed with Huffman Enconding and decompresses
         * it into an outputFile.
         * @param inputFile the path to the input file.
         * @param outputFile the path to the output file.
         */
        void run(const std::string& inputFile, const std::string& outputFile) override{
            const auto bytes = HmcReader::readBytes(inputFile);
            const auto text = ByteConverter::fromBytes(bytes);

            if (text.empty()) {
                throw std::runtime_error("Input file is empty");
            }

            auto decoded = Decoder::decode(text);
            Writer::writeString(outputFile, decoded);

            std::cout << std::format("File saved at {}", outputFile) << std::endl;
        };
};

#endif //HUFFMANENGINE_H
