/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/  

#include <libc/string/string.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/interrupts.h>

idt_desc idt[IDT_SiZE];


/*
 * @function idt_set_gate :
 *     Set an Interrupt Gate
 *     in the Interrupt Descriptor
 *     table.
 *         @param num: Interrupt Number
 *         @param handler : Interrupt Handler
 *         @param sel : Segment Selector
 *         @param flags : Flags like DPL.
 */
void idt_set_gate(uint8_t num, int_handler handler, uint16_t sel,
              uint8_t flags)
{
    idt[num].base_lo = (uint16_t)(((uintptr_t)handler >> 0) & 0xFFFF);
    idt[num].base_hi = (uint16_t)(((uintptr_t)handler >> 16) & 0xFFFF);
    idt[num].base_hi2 = (uint32_t)(((uintptr_t)handler >> 32) & 0xFFFFFFFF);
    idt[num].reserved = 0;
    idt[num].reserved2 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

 /*
  * @function init_idt:
  *   Initalizes Interupt Descriptor Table.
  *   Sets limit and base, sets all 256 
  *   descriptors to 0.
  */
  
 void init_idt()
 {
     idt_ptr idp;
     idp.limit = (sizeof(idt))-1;
     idp.base = (uintptr_t)idt; 

     memset(&idt,0,sizeof(idt));


 __asm__ __volatile__(
                            "lidt%z0 (%0)"
                            :
                            :"r"(&idp.limit)
                        );
 }





