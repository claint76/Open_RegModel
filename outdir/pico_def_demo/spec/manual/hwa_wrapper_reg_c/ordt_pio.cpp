//   Ordt 190617.01 autogenerated file 
//   Input: hwa_wrapper.rdl
//   Parms: openreg.parms
//   Date: Tue Aug 13 05:29:50 EDT 2019
//

#include "ordt_pio_common.hpp"
#include "ordt_pio.hpp"

// ------------------ ordt_addr_elem methods ------------------

ordt_addr_elem::ordt_addr_elem(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : m_startaddress(_m_startaddress),
    m_endaddress(_m_endaddress) {
}

bool  ordt_addr_elem::containsAddress(const uint64_t &addr) {
  return ((addr >= m_startaddress) && (addr <= m_endaddress));
}

bool  ordt_addr_elem::isBelowAddress(const uint64_t &addr) {
  return (addr > m_endaddress);
}

bool  ordt_addr_elem::isAboveAddress(const uint64_t &addr) {
  return (addr < m_startaddress);
}

bool  ordt_addr_elem::hasStartAddress(const uint64_t &addr) {
  return (addr == m_startaddress);
}

void  ordt_addr_elem::update_child_ptrs() {
}

// ------------------ ordt_regset methods ------------------

ordt_addr_elem*  ordt_regset::findAddrElem(const uint64_t &addr) {
  int lo = 0;
  int hi = m_children.size()-1;
  int mid = 0;
  while (lo <= hi) {
     mid = (lo + hi) / 2;
     if (m_children[mid]->containsAddress(addr)) {
        //outElem = m_children[mid];
        return m_children[mid];
     }
     else if (m_children[mid]->isAboveAddress(addr))
        hi = mid - 1;
     else
        lo = mid + 1;
  }
  return nullptr;
}

ordt_regset::ordt_regset(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_addr_elem(_m_startaddress, _m_endaddress) {
}

int  ordt_regset::write(const uint64_t &addr, const ordt_data &wdata) {
     if (this->containsAddress(addr)) {
        childElem = this->findAddrElem(addr);
        if (childElem != nullptr) { return childElem->write(addr, wdata); }
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in regset\n";
  #endif
     return 8;
}

int  ordt_regset::read(const uint64_t &addr, ordt_data &rdata) {
     if (this->containsAddress(addr)) {
        childElem = this->findAddrElem(addr);
        if (childElem != nullptr) { return childElem->read(addr, rdata); }
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in regset\n";
  #endif
     rdata.clear();
     return 8;
}

// ------------------ ordt_reg methods ------------------

ordt_reg::ordt_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_addr_elem(_m_startaddress, _m_endaddress) {
}

ordt_reg::ordt_reg(const ordt_reg &_old)
  : ordt_addr_elem(_old),
    m_mutex() {
}

void  ordt_reg::write(const ordt_data &wdata) {
}

int  ordt_reg::write(const uint64_t &addr, const ordt_data &wdata) {
     return 0;
}

void  ordt_reg::read(ordt_data &rdata) {
}

int  ordt_reg::read(const uint64_t &addr, ordt_data &rdata) {
     return 0;
}

// ------------------ ordt_rg_ral_regs_demo_CTRL methods ------------------

ordt_rg_ral_regs_demo_CTRL::ordt_rg_ral_regs_demo_CTRL(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    PRESCALER(0, 2, 0x0, r_std, w_none),
    MODE(2, 2, 0x0, r_std, w_none),
    MASTER(4, 1, 0x0, r_std, w_std),
    DORD(5, 1, 0x0, r_std, w_std),
    ENABLE(6, 1, 0x0, r_std, w_std),
    CLK2X(7, 1, 0x0, r_std, w_std) {
}

int  ordt_rg_ral_regs_demo_CTRL::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_ral_regs_demo_CTRL at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_CTRL\n";
  #endif
     return 8;
}

void  ordt_rg_ral_regs_demo_CTRL::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  PRESCALER.write(wdata);
  MODE.write(wdata);
  MASTER.write(wdata);
  DORD.write(wdata);
  ENABLE.write(wdata);
  CLK2X.write(wdata);
}

int  ordt_rg_ral_regs_demo_CTRL::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_ral_regs_demo_CTRL at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_CTRL\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_ral_regs_demo_CTRL::read(ordt_data &rdata) {
  rdata.clear();
  for (uint64_t widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  PRESCALER.read(rdata);
  MODE.read(rdata);
  MASTER.read(rdata);
  DORD.read(rdata);
  ENABLE.read(rdata);
  CLK2X.read(rdata);
}

// ------------------ ordt_rg_ral_regs_demo_INTCTRL methods ------------------

ordt_rg_ral_regs_demo_INTCTRL::ordt_rg_ral_regs_demo_INTCTRL(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    INTLVL(0, 2, 0x0, r_std, w_std) {
}

int  ordt_rg_ral_regs_demo_INTCTRL::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_ral_regs_demo_INTCTRL at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_INTCTRL\n";
  #endif
     return 8;
}

void  ordt_rg_ral_regs_demo_INTCTRL::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  INTLVL.write(wdata);
}

int  ordt_rg_ral_regs_demo_INTCTRL::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_ral_regs_demo_INTCTRL at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_INTCTRL\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_ral_regs_demo_INTCTRL::read(ordt_data &rdata) {
  rdata.clear();
  for (uint64_t widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  INTLVL.read(rdata);
}

// ------------------ ordt_rg_ral_regs_demo_STATUS methods ------------------

ordt_rg_ral_regs_demo_STATUS::ordt_rg_ral_regs_demo_STATUS(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    WRCOL(6, 1, 0x0, r_std, w_none),
    IF(7, 1, 0x0, r_std, w_none) {
}

int  ordt_rg_ral_regs_demo_STATUS::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_ral_regs_demo_STATUS at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_STATUS\n";
  #endif
     return 8;
}

void  ordt_rg_ral_regs_demo_STATUS::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  WRCOL.write(wdata);
  IF.write(wdata);
}

int  ordt_rg_ral_regs_demo_STATUS::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_ral_regs_demo_STATUS at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_STATUS\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_ral_regs_demo_STATUS::read(ordt_data &rdata) {
  rdata.clear();
  for (uint64_t widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  WRCOL.read(rdata);
  IF.read(rdata);
}

// ------------------ ordt_rg_ral_regs_demo_RCNT_SAT methods ------------------

ordt_rg_ral_regs_demo_RCNT_SAT::ordt_rg_ral_regs_demo_RCNT_SAT(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    str(16, 10, 0x0, r_clr, w_std),
    subch(26, 5, 0x0, r_clr, w_std),
    en(31, 1, 0x1, r_std, w_std) {
}

int  ordt_rg_ral_regs_demo_RCNT_SAT::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_ral_regs_demo_RCNT_SAT at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_RCNT_SAT\n";
  #endif
     return 8;
}

void  ordt_rg_ral_regs_demo_RCNT_SAT::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  str.write(wdata);
  subch.write(wdata);
  en.write(wdata);
}

int  ordt_rg_ral_regs_demo_RCNT_SAT::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_ral_regs_demo_RCNT_SAT at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_ral_regs_demo_RCNT_SAT\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_ral_regs_demo_RCNT_SAT::read(ordt_data &rdata) {
  rdata.clear();
  for (uint64_t widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  str.read(rdata);
  subch.read(rdata);
  en.read(rdata);
}

// ------------------ ordt_rset_ral_regs_demo methods ------------------

ordt_rset_ral_regs_demo::ordt_rset_ral_regs_demo(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    CTRL(_m_startaddress + 0x0, _m_startaddress + 0x3),
    INTCTRL(_m_startaddress + 0x4, _m_startaddress + 0x7),
    STATUS(_m_startaddress + 0x8, _m_startaddress + 0xb),
    RCNT_SAT(_m_startaddress + 0xc, _m_startaddress + 0xf) {
  m_children.push_back(&CTRL);
  m_children.push_back(&INTCTRL);
  m_children.push_back(&STATUS);
  m_children.push_back(&RCNT_SAT);
}

void  ordt_rset_ral_regs_demo::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&CTRL);
  m_children.push_back(&INTCTRL);
  m_children.push_back(&STATUS);
  m_children.push_back(&RCNT_SAT);
}

// ------------------ ordt_root methods ------------------

ordt_root::ordt_root()
  : ordt_root(0x0, 0xf) {
}

ordt_root::ordt_root(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    ral_regs_demo(_m_startaddress + 0x0, _m_startaddress + 0xf) {
  m_children.push_back(&ral_regs_demo);
}

void  ordt_root::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&ral_regs_demo);
}

