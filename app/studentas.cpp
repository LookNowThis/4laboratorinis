#include "studentas.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

void Studentas::logMsg(const std::string& msg) {
    std::cerr << "[RuleOfThree] " << msg << "\n";
}

Studentas::Studentas()
    : Zmogus(), egzaminas_(0), galutinis_(0.0),
      id_(s_next_id_++), karta_(0)
{
    ++s_ctor_count_;
    logMsg("Default ctor: id=" + std::to_string(id_) +
           ", gen=" + std::to_string(karta_) +
           ", this=" + std::to_string(reinterpret_cast<std::uintptr_t>(this)));
}

Studentas::Studentas(const Studentas& other)
    : Zmogus(other.vardas_, other.pavarde_),
      nd_(other.nd_),
      egzaminas_(other.egzaminas_),
      galutinis_(other.galutinis_),
      id_(s_next_id_++),
      karta_(other.karta_ + 1)
{
    ++s_copy_ctor_count_;
    logMsg("Copy ctor: new.id=" + std::to_string(id_) +
           ", from.id=" + std::to_string(other.id_) +
           ", new.gen=" + std::to_string(karta_) +
           ", this=" + std::to_string(reinterpret_cast<std::uintptr_t>(this)) +
           ", from=" + std::to_string(reinterpret_cast<std::uintptr_t>(&other)));
}

Studentas& Studentas::operator=(const Studentas& other)
{
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
        galutinis_ = other.galutinis_;
        karta_ = std::max(karta_, other.karta_);
    }
    ++s_copy_assign_count_;
    logMsg("Copy assign: id=" + std::to_string(id_) +
           " <- from.id=" + std::to_string(other.id_) +
           ", this=" + std::to_string(reinterpret_cast<std::uintptr_t>(this)) +
           ", from=" + std::to_string(reinterpret_cast<std::uintptr_t>(&other)));
    return *this;
}

Studentas::~Studentas() {
    ++s_dtor_count_;
    logMsg("Dtor: id=" + std::to_string(id_) +
           ", gen=" + std::to_string(karta_) +
           ", this=" + std::to_string(reinterpret_cast<std::uintptr_t>(this)));
    vardas_.clear();
    pavarde_.clear();
    nd_.clear();
    egzaminas_ = 0;
    galutinis_ = 0.0;
}

void Studentas::printRuleOfThreeStats(std::ostream& os) {
    os << "\n== Rule of Three statistika ==\n"
       << "Default ctor: " << s_ctor_count_ << "\n"
       << "Copy ctor:    " << s_copy_ctor_count_ << "\n"
       << "Copy assign:  " << s_copy_assign_count_ << "\n"
       << "Destructor:   " << s_dtor_count_ << "\n\n";
}

double vidurkis(const std::vector<int>& v) {
    return grades_vidurkis(v);
}
double mediana(const std::vector<int>& v) {
    return grades_mediana(v);
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    s.nd_.assign(5, 0);
    is >> s.vardas_ >> s.pavarde_;
    for (int i = 0; i < 5; i++) is >> s.nd_[i];
    is >> s.egzaminas_;
    s.perskaiciuoti(vidurkis);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(12) << s.vardas_
       << std::setw(12) << s.pavarde_
       << std::setw(10) << std::fixed << std::setprecision(2)
       << s.galutinis_;
    return os;
}

Studentas::Studentas(std::istream& is) : egzaminas_(0), galutinis_(0.0),
    id_(s_next_id_++), karta_(0)
{
    ++s_ctor_count_;
    readStudent(is);
    logMsg("Stream ctor: id=" + std::to_string(id_) +
           ", this=" + std::to_string(reinterpret_cast<std::uintptr_t>(this)));
}

std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;
    nd_.assign(5, 0);
    for (int i = 0; i < 5; ++i) is >> nd_[i];
    is >> egzaminas_;
    galutinis_ = skaiciuotiGalutini(vidurkis);
    return is;
}

double Studentas::skaiciuotiGalutini(double (*f)(const std::vector<int>&)) const {
    return 0.4 * f(nd_) + 0.6 * egzaminas_;
}

void Studentas::perskaiciuoti(double (*f)(const std::vector<int>&)) {
    galutinis_ = skaiciuotiGalutini(f);
}

void Studentas::spausdinti(std::ostream& os) const {
    os << std::left << std::setw(12) << vardas_
       << std::setw(12) << pavarde_
       << std::setw(10) << std::fixed << std::setprecision(2) << galutinis_
       << "\n";
}

bool comparePagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}
bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}
bool comparePagalGalutini(const Studentas& a, const Studentas& b) {
    return a.galutinis() < b.galutinis();
}

std::vector<Studentas> nuskaitytiIsFailo(const std::string& failas) {
    return nuskaitytiIsFailoT<std::vector<Studentas>>(failas);
}

void isvestiStudentus(const std::vector<Studentas>& gr, const std::string& failas) {
    isvestiStudentusT(gr, failas);
}

Studentas generuotiStudenta(int id) {
    Studentas s;
    s.setVardas("Vardas" + std::to_string(id));
    s.setPavarde("Pavarde" + std::to_string(id));
    std::vector<int> nd(5);
    nd.resize(5); // BUGFIX iš v1.5
    for (int i = 0; i < 5; ++i)  nd[i] = 1 + std::rand() % 10;
    s.setNd(nd);
    s.setEgzaminas(1 + std::rand() % 10);
    s.perskaiciuoti(vidurkis);
    return s;
}

void generuotiFaila(const std::string& failoVardas, int kiek) {
    std::ofstream out(failoVardas);
    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    for (int i = 1; i <= kiek; ++i) {
        out << "Vardas" << i << " "
            << "Pavarde" << i << " ";
        for (int j = 0; j < 5; ++j) out << (std::rand() % 10 + 1) << " ";
        out << (std::rand() % 10 + 1) << "\n";
    }
}

void split_strat1_vector(const std::vector<Studentas>& src,
                         std::vector<Studentas>& vargs,
                         std::vector<Studentas>& kiet)
{
    vargs.clear();
    kiet.clear();

    for (const auto& s : src) {
        if (s.galutinis() < 5.0)
            vargs.push_back(s);
        else
            kiet.push_back(s);
    }
}

void split_strat1_list(const std::list<Studentas>& src,
                       std::list<Studentas>& vargs,
                       std::list<Studentas>& kiet)
{
    vargs.clear();
    kiet.clear();

    for (const auto& s : src) {
        if (s.galutinis() < 5.0)
            vargs.push_back(s);
        else
            kiet.push_back(s);
    }
}

void split_strat2_vector(std::vector<Studentas>& grupe,
                         std::vector<Studentas>& vargs)
{
    vargs.clear();
    vargs.reserve(grupe.size());

    size_t newSize = 0;

    for (size_t i = 0; i < grupe.size(); i++) {
        if (grupe[i].galutinis() < 5.0) {
            vargs.push_back(grupe[i]);
        } else {
            grupe[newSize++] = std::move(grupe[i]);
        }
    }

    grupe.erase(grupe.begin() + newSize, grupe.end());
}

void split_strat2_list(std::list<Studentas>& grupe,
                       std::list<Studentas>& vargs)
{
    vargs.clear();

    for (auto it = grupe.begin(); it != grupe.end(); ) {
        if (it->galutinis() < 5.0) {
            vargs.push_back(*it);
            it = grupe.erase(it);
        } else {
            ++it;
        }
    }
}

void split_strat3_vector(std::vector<Studentas>& all,
                         std::vector<Studentas>& vargs)
{
    vargs.clear();
    vargs.reserve(all.size() / 2);

    std::remove_copy_if(all.begin(), all.end(),
                        std::back_inserter(vargs),
                        [](const Studentas& s){ return !(s.galutinis() < 5.0); });

    auto it = std::remove_if(all.begin(), all.end(),
                             [](const Studentas& s){ return s.galutinis() < 5.0; });

    all.erase(it, all.end());

    all.shrink_to_fit();
    vargs.shrink_to_fit();
}

void split_strat3_list(std::list<Studentas>& all,
                       std::list<Studentas>& vargs)
{
    split_strat2_list(all, vargs);
}

