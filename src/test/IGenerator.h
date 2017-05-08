// Кодировка utf-8.
#ifndef TESTS_IGENERATOR_H_
#define TESTS_IGENERATOR_H_

#include "Structures.h"
#include "IPrinter.h"
#include "IFixture.h"
#include <algorithm>

namespace Cpp11_unit {

    class IGenerator {
    public:

        bool switchOnNew() {
            auto isMayTakeNext = areThereElements();
            if (isMayTakeNext) {
                switchOnNewElem();
            }
            for (auto &genPtr : m_attachedGen) {
                if (genPtr->areThereElements() || 
                    std::any_of(genPtr->m_attachedGen.begin(), genPtr->m_attachedGen.end(),
                        [](IGenerator* childGen) {return childGen->areThereElements();}
                    )
                ) {
                    genPtr->switchOnNew();
                    isMayTakeNext = true;
                }   
            }
            if (isMayTakeNext == false) {
                _isNeedReInit = true;
                for (auto &genPtr : m_attachedGen) {
                    genPtr->_isNeedReInit = true;
                }
            }
            return isMayTakeNext;
        }

        virtual bool isNeedReInit() final {
            return _isNeedReInit;
        }

        void attach(IGenerator *other) {
            m_attachedGen.push_back(other);
        }

    protected:
        virtual bool areThereElements() = 0;
        virtual void switchOnNewElem() = 0;
        Container<IGenerator *> m_attachedGen{};
        bool _isNeedReInit = false;
    };

    template<typename Result>
    class GeneratorBase : public IGenerator {
    public:
        
        virtual const Result & Get() final {
            if (m_currentElemPtr == nullptr) {
                // throw std::logic_error("Get value from generator before switchOnNew");
                switchOnNewElem();
            }            
            return *m_currentElemPtr;
        }

    protected:

        GeneratorBase(size_t maxLength)
            : m_maxElementNumber(maxLength)
        {}

        GeneratorBase() {}

        virtual Result getNewElement() = 0;
        
        virtual bool areThereElements() override {
            if (m_maxElementNumber > m_elementNumber) {
                return true;
            } else {
                return false;
            }
        }

        void setMaxLength(size_t maxLength) {
            m_maxElementNumber = maxLength;
        }

    private:

        virtual void switchOnNewElem() override {
            m_currentElemPtr.reset(new Result(getNewElement()));
            m_elementNumber++;
        }

        std::unique_ptr<Result> m_currentElemPtr = nullptr;
        size_t m_maxElementNumber = 1;
        size_t m_elementNumber = 0;
    };

    class GeneratorsKeeper {
    protected:
        GeneratorsKeeper()
        {}

        void addGenerator(IGenerator *generator) {
            m_activeGenPtrs.push_back(generator);
        }
    public:
        // If false mean it's in the beggining state and previous cicle over
        bool switchGenerator() {
            if (m_activeGenPtrs.empty()) {
                m_activeGenPtrs.swap(m_doneGenPtrs);
                return false;
            }
            if (m_activeGenPtrs.back()->switchOnNew() == true) {
                std::move(m_doneGenPtrs.begin(), m_doneGenPtrs.end(), std::back_inserter(m_activeGenPtrs));
                m_doneGenPtrs.clear();
                return true;
            } else {
                m_doneGenPtrs.push_front(m_activeGenPtrs.back());
                m_activeGenPtrs.pop_back();
                return switchGenerator();
            }
        }
    private:
        Container<IGenerator *> m_doneGenPtrs{};
        Container<IGenerator *> m_activeGenPtrs{};
    };

} //namespace Cpp11_unit

#endif //TESTS_IGENERATOR_H_
