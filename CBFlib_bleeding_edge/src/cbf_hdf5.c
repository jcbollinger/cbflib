/**********************************************************************
 * cbf_hdf5 -- read and write HDF5/NeXus files                        *
 *                                                                    *
 * Version 0.9.5 27 April 2014                                        *
 *                                                                    *
 *                          Paul Ellis and                            *
 *         Herbert J. Bernstein (yaya@bernstein-plus-sons.com)        *
 *                                                                    *
 * (C) Copyright 2009, 2012, 2013, 2014 Herbert J. Bernstein          *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 * YOU MAY REDISTRIBUTE THE CBFLIB PACKAGE UNDER THE TERMS OF THE GPL *
 *                                                                    *
 * ALTERNATIVELY YOU MAY REDISTRIBUTE THE CBFLIB API UNDER THE TERMS  *
 * OF THE LGPL                                                        *
 *                                                                    *
 **********************************************************************/

/*************************** GPL NOTICES ******************************
 *                                                                    *
 * This program is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU General Public License as     *
 * published by the Free Software Foundation; either version 2 of     *
 * (the License, or (at your option) any later version.               *
 *                                                                    *
 * This program is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * along with this program; if not, write to the Free Software        *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA           *
 * 02111-1307  USA                                                    *
 *                                                                    *
 **********************************************************************/

/************************* LGPL NOTICES *******************************
 *                                                                    *
 * This library is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU Lesser General Public         *
 * License as published by the Free Software Foundation; either       *
 * version 2.1 of the License, or (at your option) any later version. *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 * Lesser General Public License for more details.                    *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License along with this library; if not, write to the Free         *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    *
 * MA  02110-1301  USA                                                *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                    Stanford University Notices                     *
 *  for the CBFlib software package that incorporates SLAC software   *
 *                 on which copyright is disclaimed                   *
 *                                                                    *
 * This software                                                      *
 * -------------                                                      *
 * The term "this software", as used in these Notices, refers to      *
 * those portions of the software package CBFlib that were created by *
 * employees of the Stanford Linear Accelerator Center, Stanford      *
 * University.                                                        *
 *                                                                    *
 * Stanford disclaimer of copyright                                   *
 * --------------------------------                                   *
 * Stanford University, owner of the copyright, hereby disclaims its  *
 * copyright and all other rights in this software.  Hence, anyone    *
 * may freely use it for any purpose without restriction.             *
 *                                                                    *
 * Acknowledgement of sponsorship                                     *
 * ------------------------------                                     *
 * This software was produced by the Stanford Linear Accelerator      *
 * Center, Stanford University, under Contract DE-AC03-76SFO0515 with *
 * the Department of Energy.                                          *
 *                                                                    *
 * Government disclaimer of liability                                 *
 * ----------------------------------                                 *
 * Neither the United States nor the United States Department of      *
 * Energy, nor any of their employees, makes any warranty, express or *
 * implied, or assumes any legal liability or responsibility for the  *
 * accuracy, completeness, or usefulness of any data, apparatus,      *
 * product, or process disclosed, or represents that its use would    *
 * not infringe privately owned rights.                               *
 *                                                                    *
 * Stanford disclaimer of liability                                   *
 * --------------------------------                                   *
 * Stanford University makes no representations or warranties,        *
 * express or implied, nor assumes any liability for the use of this  *
 * software.                                                          *
 *                                                                    *
 * Maintenance of notices                                             *
 * ----------------------                                             *
 * In the interest of clarity regarding the origin and status of this *
 * software, this and all the preceding Stanford University notices   *
 * are to remain affixed to any copy or derivative of this software   *
 * made or distributed by the recipient and are to be affixed to any  *
 * copy of software made or distributed by the recipient that         *
 * contains a copy or derivative of this software.                    *
 *                                                                    *
 * Based on SLAC Software Notices, Set 4                              *
 * OTT.002a, 2004 FEB 03                                              *
 **********************************************************************/



/**********************************************************************
 *                               NOTICE                               *
 * Creative endeavors depend on the lively exchange of ideas. There   *
 * are laws and customs which establish rights and responsibilities   *
 * for authors and the users of what authors create.  This notice     *
 * is not intended to prevent you from using the software and         *
 * documents in this package, but to ensure that there are no         *
 * misunderstandings about terms and conditions of such use.          *
 *                                                                    *
 * Please read the following notice carefully.  If you do not         *
 * understand any portion of this notice, please seek appropriate     *
 * professional legal advice before making use of the software and    *
 * documents included in this software package.  In addition to       *
 * whatever other steps you may be obliged to take to respect the     *
 * intellectual property rights of the various parties involved, if   *
 * you do make use of the software and documents in this package,     *
 * please give credit where credit is due by citing this package,     *
 * its authors and the URL or other source from which you obtained    *
 * it, or equivalent primary references in the literature with the    *
 * same authors.                                                      *
 *                                                                    *
 * Some of the software and documents included within this software   *
 * package are the intellectual property of various parties, and      *
 * placement in this package does not in any way imply that any       *
 * such rights have in any way been waived or diminished.             *
 *                                                                    *
 * With respect to any software or documents for which a copyright    *
 * exists, ALL RIGHTS ARE RESERVED TO THE OWNERS OF SUCH COPYRIGHT.   *
 *                                                                    *
 * Even though the authors of the various documents and software      *
 * found here have made a good faith effort to ensure that the        *
 * documents are correct and that the software performs according     *
 * to its documentation, and we would greatly appreciate hearing of   *
 * any problems you may encounter, the programs and documents any     *
 * files created by the programs are provided **AS IS** without any   *
 * warranty as to correctness, merchantability or fitness for any     *
 * particular or general use.                                         *
 *                                                                    *
 * THE RESPONSIBILITY FOR ANY ADVERSE CONSEQUENCES FROM THE USE OF    *
 * PROGRAMS OR DOCUMENTS OR ANY FILE OR FILES CREATED BY USE OF THE   *
 * PROGRAMS OR DOCUMENTS LIES SOLELY WITH THE USERS OF THE PROGRAMS   *
 * OR DOCUMENTS OR FILE OR FILES AND NOT WITH AUTHORS OF THE          *
 * PROGRAMS OR DOCUMENTS.                                             *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                           The IUCr Policy                          *
 *      for the Protection and the Promotion of the STAR File and     *
 *     CIF Standards for Exchanging and Archiving Electronic Data     *
 *                                                                    *
 * Overview                                                           *
 *                                                                    *
 * The Crystallographic Information File (CIF)[1] is a standard for   *
 * information interchange promulgated by the International Union of  *
 * Crystallography (IUCr). CIF (Hall, Allen & Brown, 1991) is the     *
 * recommended method for submitting publications to Acta             *
 * Crystallographica Section C and reports of crystal structure       *
 * determinations to other sections of Acta Crystallographica         *
 * and many other journals. The syntax of a CIF is a subset of the    *
 * more general STAR File[2] format. The CIF and STAR File approaches *
 * are used increasingly in the structural sciences for data exchange *
 * and archiving, and are having a significant influence on these     *
 * activities in other fields.                                        *
 *                                                                    *
 * Statement of intent                                                *
 *                                                                    *
 * The IUCr's interest in the STAR File is as a general data          *
 * interchange standard for science, and its interest in the CIF,     *
 * a conformant derivative of the STAR File, is as a concise data     *
 * exchange and archival standard for crystallography and structural  *
 * science.                                                           *
 *                                                                    *
 * Protection of the standards                                        *
 *                                                                    *
 * To protect the STAR File and the CIF as standards for              *
 * interchanging and archiving electronic data, the IUCr, on behalf   *
 * of the scientific community,                                       *
 *                                                                    *
 * * holds the copyrights on the standards themselves,                *
 *                                                                    *
 * * owns the associated trademarks and service marks, and            *
 *                                                                    *
 * * holds a patent on the STAR File.                                 *
 *                                                                    *
 * These intellectual property rights relate solely to the            *
 * interchange formats, not to the data contained therein, nor to     *
 * the software used in the generation, access or manipulation of     *
 * the data.                                                          *
 *                                                                    *
 * Promotion of the standards                                         *
 *                                                                    *
 * The sole requirement that the IUCr, in its protective role,        *
 * imposes on software purporting to process STAR File or CIF data    *
 * is that the following conditions be met prior to sale or           *
 * distribution.                                                      *
 *                                                                    *
 * * Software claiming to read files written to either the STAR       *
 * File or the CIF standard must be able to extract the pertinent     *
 * data from a file conformant to the STAR File syntax, or the CIF    *
 * syntax, respectively.                                              *
 *                                                                    *
 * * Software claiming to write files in either the STAR File, or     *
 * the CIF, standard must produce files that are conformant to the    *
 * STAR File syntax, or the CIF syntax, respectively.                 *
 *                                                                    *
 * * Software claiming to read definitions from a specific data       *
 * dictionary approved by the IUCr must be able to extract any        *
 * pertinent definition which is conformant to the dictionary         *
 * definition language (DDL)[3] associated with that dictionary.      *
 *                                                                    *
 * The IUCr, through its Committee on CIF Standards, will assist      *
 * any developer to verify that software meets these conformance      *
 * conditions.                                                        *
 *                                                                    *
 * Glossary of terms                                                  *
 *                                                                    *
 * [1] CIF:  is a data file conformant to the file syntax defined     *
 * at http://www.iucr.org/iucr-top/cif/spec/index.html                *
 *                                                                    *
 * [2] STAR File:  is a data file conformant to the file syntax       *
 * defined at http://www.iucr.org/iucr-top/cif/spec/star/index.html   *
 *                                                                    *
 * [3] DDL:  is a language used in a data dictionary to define data   *
 * items in terms of "attributes". Dictionaries currently approved    *
 * by the IUCr, and the DDL versions used to construct these          *
 * dictionaries, are listed at                                        *
 * http://www.iucr.org/iucr-top/cif/spec/ddl/index.html               *
 *                                                                    *
 * Last modified: 30 September 2000                                   *
 *                                                                    *
 * IUCr Policy Copyright (C) 2000 International Union of              *
 * Crystallography                                                    *
 **********************************************************************/



#ifdef __cplusplus

extern "C" {

#endif

#include "cbf.h"
#include "cbf_tree.h"
#include "cbf_hdf5.h"
#include "cbf_ascii.h"
#include "cbf_binary.h"
#include "cbf_compress.h"
#include "cbf_file.h"
#include "cbf_write.h"
#include "cbf_write_binary.h"
#include "cbf_read_mime.h"
#include "cbf_string.h"
#include "cbf_codes.h"
#include "cbf_alloc.h"
#include "cbf_simple.h"
#include "cbf_tree.h"
#include "cbf_hdf5_filter.h"
#ifdef CBF_USE_ULP
#include "cbf_ulp.h"
#endif
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <errno.h>

    static int cbf_find_array_data_h5type
    (hid_t * const type,
     unsigned int bits,
     int sign,
     int real,
     const char *byteorder);

    /* CBF column -- NeXus DataSet Mapping Tables
     applicable to categories that map to
     datasets or to attributes

     In each of the names the constructs
     $(cifcolumn)
     $(cifcolumn,rownum)
     $(_category.cifcolumn,rownum)
     will be replaced by the value of the specified
     CIF tag at the current row, or at the specified
     row.  Failure to find the designated item, will
     cause a fail-through in $or to the next argument.

     The construct $axis(value) is replaced by x, y or z
     for values of 1, 2 and 3, respectively, after
     evaluating value.

     The construct $matchrow(tag,value) is replaced by the row number
     in the category for the tag that matches the value given

     The construct $matchrowmax(tag,value,controlcolumn) is replaced by the row number
     in the category for the tag that matches the value given, subject to maximizing
     the value of the control column in the category of tag.

     The construct $matchcase(tag1,value1,expression1,tag2,value2,expression2,...,expressionn)

     The contruct $or(arg1,arg2,arg3) is replaced by the first
     of the arguments that can be successfully evaluated

     The construct $equipment(value) is replaced by
     CBF_diffrn_detector__$(_diffrn_detector.id,0):NXdetector
     CBF_diffrn_measurement__$(_diffrn_measurement.diffrn_id,0):NXsample
     coordinate_system:NXcoordinate_system
     and $equipment_class(value) is replaced by
     NXdetector
     NXsample
     Nxcoordinate_system
     for the values "detector", "goniometer", or "general"
     respectively
     */

    /*  The top of the target tree is

     /CBF_diffrn_scan__SCANID:NXentry
     /CBF_scan_id="SCANID"
     /CBF_diffrn_id="DIFFRNID"
     /CBF_entry_id="ENTRYID"
     /instrument:NXinstrument

     */

    typedef struct {
        int    objtype;          /* CBF_H5_COLUMN_GROUP
                                  or CBF_H5_COLUMN_DATASET
                                  possibly ored with CBF_H5_TERMINATE
                                  */
        const char * h5pathelement;    /* An hdf5 path element
                                        and optional class*/
    } cbf_h5path_element;

    typedef struct {
        int    dsorat;       /* CBF_H5_COLUMN_DATASET
                              or CBF_H5_COLUMN_ATTRIBUTE */
        int    parent_index; /* index into the cbfcol_h5parent table
                              If the parent_index is -1, the new
                              items goes in at the same level
                              as the first item in the cbfcol_h5parent
                              as a sibling.
                              */

        char * cifcolumn;    /* the name of the cif column to be mapped */
        char * mappedname;   /* the hdf5 target name or NULL to use parent */
        char * units;        /* units or NULL */
        int numeric;         /* CBF_H5_TEXT, CBF_H5_FLOAT, CBF_H5_INTEGER */
        int special;         /* 0 for normal handling, 1 for special case,
                              add CBF_H5_TERMINATE for terminal */
    } cbf_colnxdsat;

    typedef struct {
        char * cifcategory;  /* the name of the cf category to be mapped */
        cbf_h5path_element * h5path;
        /* the array of nexus path elements used to map
         this category */
        cbf_colnxdsat  * nxmapping;
        /* the array of mappings of columns into datasets
         and attributes */
    } cbf_catnxmapping;


    /* column mappings for ARRAY_DATA */

    cbf_h5path_element cbf_nxmapping_array_data_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "data__$(array_id)_$(binary_id)"}
    };
    cbf_colnxdsat cbf_nxmapping_array_data[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "id", "CBF_array_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "binary_id", "CBF_binary_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "data", NULL,NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "header_contents",   "CBF_header_contents",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "header_convention", "CBF_header_convention",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,CBF_H5_TERMINATE}
    };

    /* column mappings for ARRAY_ELEMENT_SIZE */

    cbf_h5path_element cbf_nxmapping_array_element_size_data_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE,
            "$axis($(index))_pixel_size_$(array_id):m"}
    };
    cbf_colnxdsat cbf_nxmapping_array_element_size[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "id", "CBF_array_id",NULL,0,0},
        {CBF_H5_COLUMN_DATASET, 2, "size", "$axis($(index))_pixel_size_$(array_id)","m",CBF_H5_FLOAT,CBF_H5_TERMINATE}
    };

    /* column mappings for ARRAY_INTENSITIES */

    cbf_h5path_element cbf_nxmapping_array_intensities_data_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "data__$(array_id)_$(binary_id)"}
    };
    cbf_colnxdsat cbf_nxmapping_array_intensities[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "array_id", "CBF_array_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "binary_id", "CBF_binary_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "details", "CBF_array_intensities__details",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "gain", "CBF_array_intensities__gain",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "gain_esd", "CBF_array_intensities__gain_esd",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "linearity", "CBF_array_intensities__linearity",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "offset", "CBF_array_intensities__offset",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "scaling", "CBF_array_intensities__scaling",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "overload", "CBF_array_intensities__overload",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "undefined_value", "CBF_array_intensities__undefined_value",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "pixel_fast_bin_size", "CBF_array_intensities__pixel_fast_bin_size",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "pixel_slow_bin_size", "CBF_array_intensities__pixel_slow_bin_size",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "pixel_binning_method",
            "CBF_array_intensities__pixel_binning_method",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,CBF_H5_TERMINATE}
    };


    /* column mappings for ARRAY_STRUCTURE_LIST */

    cbf_h5path_element cbf_nxmapping_array_structure_list_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "CBF_array_structure_list__$(axis_set_id)"}
    };
    cbf_colnxdsat cbf_nxmapping_array_structure_list[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "axis_set_id", "CBF_array_structure_list__axis_set_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "array_id", "CBF_array_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "dimension", "CBF_array_structure_list__dimension",NULL,CBF_H5_INTEGER|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "direction", "CBF_array_structure_list__direction",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "index", "CBF_array_structure_list__index",NULL,CBF_H5_INTEGER|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "precedence", "CBF_array_structure_list__precedence",NULL,CBF_H5_INTEGER|CBF_H5_ARRAY,CBF_H5_TERMINATE}
    };

    /* column mappings for ARRAY_STRUCTURE_LIST_SECTION */

    cbf_h5path_element cbf_nxmapping_array_structure_list_section_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "CBF_array_structure_list_section__$(id)"}
    };
    cbf_colnxdsat cbf_nxmapping_array_structure_list_section[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "array_id", "CBF_array_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "id", "CBF_section_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "index", "CBF_array_structure_list_section__index",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "end", "CBF_array_structure_list_section__end",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "start", "CBF_array_structure_list_section__start",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "stride", "CBF_array_structure_list_section__stride",NULL,CBF_H5_INTEGER,CBF_H5_TERMINATE}
    };


    /* column mappings for ARRAY_STRUCTURE_LIST_AXIS */

    cbf_h5path_element cbf_nxmapping_array_structure_list_axis_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "$(axis_id)"}
    };
    cbf_colnxdsat cbf_nxmapping_array_structure_list_axis[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "axis_id", "CBF_array_structure_list_axis__axis_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "axis_set_id", "CBF_array_structure_list_axis__axis_set_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "angle", "CBF_array_structure_list_axis__angle",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "angle_increment", "CBF_array_structure_list_axis__angle_FLOAT|CBF_H5_ARRAY",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "displacement", "CBF_array_structure_list_axis__displacement",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "fract_displacement", "CBF_array_structure_list_axis__fract_displacement",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "displacement_increment", "CBF_array_structure_list_axis__displacement_increment",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "fract_displacement_increment", "CBF_array_structure_list_axis__fract_displacement_increment",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "angular_pitch", "CBF_array_structure_list_axis__angular_pitch",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "radial_pitch", "CBF_array_structure_list_axis__radial_pitch",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "reference_angle", "CBF_array_structure_list_axis__reference_angle",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "reference_displacement", "CBF_array_structure_list_axis__reference_displacement",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,CBF_H5_TERMINATE}
    };

    /* column mappings for AXIS */

    cbf_h5path_element cbf_nxmapping_axis_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP,
            "$ifeq($(_axis.equipment,$match(_axis.id,$(axis_id))),detector,$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdectector,"
            "$(_axis.equipment,$match(_axis.id,$(axis_id))),goniometer,$or(CBF_diffrn_measurement__$(_diffrn_measurement.id,0),goniometer):NXsample,"
            "detector:NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "$(id)"}
    };
    cbf_colnxdsat cbf_nxmapping_axis[] = {
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "depends_on", "depends_on",NULL,CBF_H5_TEXT,CBF_H5_COLUMN_PATH},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "offset[?]", "offset","mm",CBF_H5_FLOAT,CBF_H5_COLUMN_MAP_AXES},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "type", "transformation_type",NULL,CBF_H5_TEXT,CBF_H5_COLUMN_MAP_AXES},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "system", "system",NULL,CBF_H5_TEXT,CBF_H5_COLUMN_MAP_AXES},
        {CBF_H5_COLUMN_ATTRIBUTE, 3, "vector[?]", "vector",NULL,CBF_H5_FLOAT,CBF_H5_COLUMN_MAP_AXES|CBF_H5_TERMINATE},
    };

    /* column mappings for DIFFRN_DATA_FRAME */

    cbf_h5path_element cbf_nxmapping_diffrn_data_frame_path[] = {

        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_data_frame[] = {
        {CBF_H5_COLUMN_DATASET, 2, "array_section_id", "CBF_diffrn_data_frame__section_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "array_id", "CBF_diffrn_data_frame__section_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "binary_id", "CBF_diffrn_data_frame__binary_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "center_fast", "CBF_diffrn_data_frame__center_fast_slow["
            "$(_diffrn_scan_frame.frame_number,$matchrow(_diffrn_scan_frame.frame_id,_diffrn_data_frame.id),0,"
            "$matchrow(diffrn_detector_element.id,_diffrn_data_frame.detector_element_id)],$(center_units)",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "center_slow", "CBF_diffrn_data_frame__center_fast_slow["
            "$(_diffrn_scan_frame.frame_number,$matchrow(_diffrn_scan_frame.frame_id,$(_diffrn_data_frame.id)),1,"
            "$matchrow(diffrn_detector_element.id,_diffrn_data_frame.detector_element_id)],$(center_units)",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "details", "CBF_diffrn_data_frame__details["
            "$(_diffrn_scan_frame.frame_number,$matchrow(_diffrn_scan_frame.frame_id,_diffrn_data_frame.id),"
            "$matchrow(diffrn_detector_element.id,_diffrn_data_frame.detector_element_id)]",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,CBF_H5_TERMINATE}
    };


    /* column mappings for DIFFRN_DETECTOR */

    cbf_h5path_element cbf_nxmapping_diffrn_detector_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "CBF_diffrn_detector__id"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_detector[] = {
        {CBF_H5_COLUMN_DATASET, 0, "diffrn_id", "CBF_diffrn_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "id", "CBF_diffrn_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "details", "details",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "detector", "type",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "dtime", "deadtime",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "number_of_axes", "number_of_axes",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "type", "instrument",NULL,CBF_H5_TEXT,CBF_H5_TERMINATE},
    };


    /* column mappings for DIFFRN_DETECTOR_AXIS */

    cbf_h5path_element cbf_nxmapping_diffrn_detector_axis_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"},
        {CBF_H5_COLUMN_DATASET|CBF_H5_TERMINATE, "$(axis_id)"}
    };
    cbf_colnxdsat * cbf_nxmapping_diffrn_detector_axis = NULL;


    /* column mappings for DIFFRN_DETECTOR_ELEMENT */

    cbf_h5path_element cbf_nxmapping_diffrn_detector_element_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_detector_element[] = {
        {CBF_H5_COLUMN_DATASET, 2, "id",
            "CBF_diffrn_detector_element__id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "detector_id",
            "CBF_diffrn_detector_element__detector_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "reference_center_fast",
            "CBF_diffrn_detector_element__reference_center_fast","$(reference_center_units)",CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "reference_center_slow",
            "CBF_diffrn_detector_element__reference_center_slow","$(reference_center_units)",CBF_H5_FLOAT|CBF_H5_ARRAY,CBF_H5_TERMINATE},
    };

    /* column mappings for DIFFRN_MEASUREMENT */

    cbf_h5path_element cbf_nxmapping_diffrn_measurement_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "instrument:NXinstrument"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_measurement[] = {
        {CBF_H5_COLUMN_DATASET, 0, "diffrn_id",
            "CBF_diffrn_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "details",
            "CBF_diffrn_measurement__details",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "device",
            "CBF_diffrn_measurement__device",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "device_details",
            "CBF_diffrn_measurement__device_details",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "device_type",
            "CBF_diffrn_measurement__device_type",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "id",
            "CBF_diffrn_measurement__id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "method",
            "CBF_diffrn_measurement__method",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 1, "number_of_axes",
            "CBF_diffrn_measurement__number_of_axes",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_DATASET, 1, "sample_detector_distance",
            "distance","mm",CBF_H5_FLOAT,CBF_H5_LINK},
        {CBF_H5_LINK, 1, "sample_detector_distance",
            "$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id):NXentry"
            "/instrument:NXinstrument"
            "/$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector",
            NULL,0,CBF_H5_LINK},
        {CBF_H5_COLUMN_DATASET, 1, "sample_detector_voffset",
            "CBF_diffrn_measurement__sample_detector_voffset","mm",CBF_H5_FLOAT,CBF_H5_SPECIAL},
        {CBF_H5_COLUMN_DATASET, 1, "specimen_support",
            "CBF_diffrn_measurement__specimen_support",NULL,CBF_H5_TEXT,0}
    };


    /* column mappings for DIFFRN_MEASUREMENT_AXIS */

    cbf_h5path_element cbf_nxmapping_diffrn_measurement_axis_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP,"instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE,
            "CBF_diffrn_measurement__$(measurement_id):NXsample"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_measurement_axis[] = {
        {CBF_H5_COLUMN_DATASET, 1, "axis_id",
            "CBF_axis__axis_id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 1, "measurement_device",
            "CBF_axis__measurement_device",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 1, "measurement_device",
            "CBF_axis__measurement_device",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,CBF_H5_TERMINATE},
    };

    /* column mappings for DIFFRN_RADIATION */

    cbf_h5path_element cbf_nxmapping_diffrn_radiation_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "collimator:NXcollimator"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_radiation[] = {
        {CBF_H5_COLUMN_DATASET, 2, "collimation",
            "CBF_diffrn_radiation__collimation",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 0, "diffrn_id",
            "CBF_diffrn_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "div_x_source",
            "divergence_x","degrees",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "div_y_source",
            "divergence_y","degrees",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "div_x_y_source",
            "CBF_diffrn_radiation__div_x_y_source","deg^2",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "filter_edge",
            "CBF_diffrn_radiation__filter_edge","angstroms",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "inhomogeneity",
            "CBF_diffrn_radiation__inhomogeneity","mm",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "monochromator",
            "CBF_diffrn_radiation__monochromator",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "polarisn_norm",
            "CBF_diffrn_radiation__polarisn_norm","degrees",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "polarisn_ratio",
            "CBF_diffrn_radiation__polarisn_ratio",NULL,CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "polarizn_source_norm",
            "CBF_diffrn_radiation__polarizn_source_norm","degrees",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "polarizn_source_ratio",
            "CBF_diffrn_radiation__polarizn_source_ratio",NULL,CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 2, "probe",
            "CBF_diffrn_radiation__probe",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "type",
            "CBF_diffrn_radiation__type",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "xray_symbol",
            "CBF_diffrn_radiation__xray_symbol",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 2, "wavelength_id",
            "CBF_diffrn_radiation__wavelength_id",NULL,CBF_H5_TEXT,CBF_H5_MORE},
        {CBF_H5_COLUMN_DATASET, 2, "$(_diffrn_radiation_wavelength.wavelength,$matchrowmax(_diffrn_radiation_wavelength.id,wavelength_id,_diffrn_radiation_wavelength.wt)","wavelength","angstroms",CBF_H5_FLOAT,0},
    };


    /* column mappings for DIFFRN_RADIATION_WAVELENGTH */

    cbf_h5path_element cbf_nxmapping_diffrn_radiation_wavelength_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "collimator:NXcollimator"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_radiation_wavelength[] = {
        {CBF_H5_COLUMN_DATASET, 2, "id",
            "CBF_diffrn_radiation_wavelength__id",NULL,CBF_H5_TEXT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "wavelength",
            "CBF_diffrn_radiation_wavelength__wavelength","angstroms",CBF_H5_FLOAT|CBF_H5_ARRAY,0},
        {CBF_H5_COLUMN_DATASET, 2, "wt",
            "CBF_diffrn_radiation_wavelength__wt",NULL,CBF_H5_FLOAT|CBF_H5_ARRAY,0}
    };


    /* column mappings for DIFFRN_SCAN */

    cbf_h5path_element cbf_nxmapping_diffrn_scan_path[] = {
        {CBF_H5_COLUMN_GROUP,"$or(CBF_diffrn_scan__$(_diffrn_scan.id),"
            "CBF_diffrn__$(_diffrn.id),"
            "CBF_entry__$(_entry.id),"
            "entry):NXentry"},
        {CBF_H5_COLUMN_GROUP, "instrument:NXinstrument"},
        {CBF_H5_COLUMN_GROUP|CBF_H5_TERMINATE, "$or(CBF_diffrn_detector__$(_diffrn_detector.id,0),detector):NXdetector"}
    };
    cbf_colnxdsat cbf_nxmapping_diffrn_scan[] = {
        {CBF_H5_COLUMN_DATASET, 0, "$(id)", "CBF_scan_id",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(date_end)", "end_time",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(date_start)", "start_time",NULL,CBF_H5_TEXT,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(integration_time)", "average_count_time","sec",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(_diffrn_scan_frame.frame_number,$matchrow(_diffrn_scan_frame.frame_id,$(frame_id_start))", "frame_start_number",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(_diffrn_scan_frame.frame_number,$matchrow(_diffrn_scan_frame.frame_id,$(frame_id_end))", "frame_end_number",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(frames)", "CBF_diffrn_scan__frames",NULL,CBF_H5_INTEGER,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(time_period)", "frame_time","sec",CBF_H5_FLOAT,0},
        {CBF_H5_COLUMN_DATASET, 0, "$(time_rstrt_inc$", "frame_restart_time","sec",CBF_H5_FLOAT,0}
    };


    /* Macros to get the current location in a file in form `file:line' */

#define __STR2(n) #n
#define __STR(n) __STR2(n)

/*
     Call a function if 'error' is 'CBF_SUCCESS', always printing an error message if it fails.
Require a terminating semi-colon to make it behave as a statement.
*/
#define CBF_CALL(exp) \
CBFM_PROLOG { \
if (CBF_SUCCESS==error) { \
if (CBF_SUCCESS!=(error|=(exp))) { \
cbf_debug_print(cbf_strerror(error)) \
	} \
} \
} CBFM_EPILOG

    
/*
     Call an HDF5 function unconditionally, reporting any errors.
     Only use this if 'exp' should return negative values on failure.
     This should only be defined within the cbf_H5* functions,
     as it isn't helpful everywhere.
*/


#define CBF_H5CALL(exp) \
CBFM_PROLOG { \
const int err = (exp); \
if (err < 0) { \
error |= CBF_H5ERROR; \
cbf_debug_print2("%s", "'" #exp "' failed"); \
} \
} CBFM_EPILOG
    
    
	/**
	Concatenate several null-terminated strings into a single string, with each component
	separated by one 'sep' character. A leading or trailing empty string will cause a
	leading or trailing 'sep' character to be written, the character may be repeated by
	inserting an empty string into the 'parts' array at the appropriate place. The 'parts'
	array must be terminated by a null pointer, not a pointer to an empty string.

	Examples:
	_cbf_str_join({0},c);
	→ ""
	_cbf_str_join({"string",0},c);
	→ "string"
	_cbf_str_join({"","",0},'#');
	→ "#"
	_cbf_str_join({"multi","part","string",0},'-');
	→ "multi-part-string"
	_cbf_str_join({"A","string","","with","more","separators",0},'_');
	→ "A_string__with_more_separators"
	_cbf_str_join({"","leading",0},'_');
	→ "_leading"
	_cbf_str_join({"trailing","",0},'_');
	→ "trailing_"

	Returns a string which must be free'd on success, NULL on failure.
	Creating an empty string is not failure to create a string.
	*/
	char * _cbf_strjoin(const char * const * const parts, const char sep)
	{
		/* define local variables & check the argument */
		size_t len = 0, n = 0;
		const char * const * p = parts;
		if (!parts) return NULL;
		/* get the combined length of all component strings, and the number of them */
		while (*p) {
			len += strlen(*p++);
			++n;
		}
		if (0 == n) {
			char * const str = malloc(sizeof(char));
			if (!str) return NULL;
			return strcpy(str,"");
		} else {
			/*
			Allocate a new string with enough room for every component of
			the path, N-1 1-character path seperators & a null-terminator.
			*/
			char * const str = malloc((len+n)*sizeof(char));
			if (!str) return NULL;
			char * c = str;
			for (p = parts; *p; ) {
				c = strcpy(c,*p) + strlen(*p);
				if (!*++p) break;
				*c++ = sep;
			}
			return str;
		}
	}

	/*
     The 'strdup' function isn't available when compiling with -ansi on GCC, so provide an alternative.
     */
	static char * _cbf_strdup(const char *s)
	{
		return s ? strcpy(malloc(sizeof(char)*(1+strlen(s))),s) : 0;
	}

    
    /****************************************************************
    Store & manuipluate a set of keys identifying a set of data of interest.
     ****************************************************************/

	/**
	Map an axis set ID to a direction, for use in extracting axis data for images.
         */
    typedef struct cbf_arrayAxisSet_t {
		unsigned int count;
		const char * * axis_set_id;
		const char * * path;
		unsigned int * index;
		unsigned int * precedence;
		unsigned int * dimension;
		const char * * direction;
	} cbf_arrayAxisSet_t;

	static cbf_arrayAxisSet_t _cbf_make_arrayAxisSet()
	{
		cbf_arrayAxisSet_t obj;
		obj.count = 0;
		obj.axis_set_id = NULL;
		obj.path = NULL;
		obj.index = NULL;
		obj.precedence = NULL;
		obj.dimension = NULL;
		obj.direction = NULL;
		return obj;
	}

	static void _cbf_free_arrayAxisSet(const cbf_arrayAxisSet_t obj)
	{
		const char * const * const path_end = obj.path + obj.count;
		const char * const * p;
		for (p = obj.path; path_end != p; ++p) free((void*)(*p));
		free((void*)obj.axis_set_id);
		free((void*)obj.path);
		free((void*)obj.index);
		free((void*)obj.precedence);
		free((void*)obj.dimension);
		free((void*)obj.direction);
	}

	static int _cbf_insert_arrayAxisSet
			(cbf_arrayAxisSet_t * const obj,
			 const char * const axis_set_id,
     const char * const path,
     unsigned int index,
			 unsigned int precedence,
			 unsigned int dimension,
			 const char * const direction)
	{
		if (!obj) {
			return CBF_ARGUMENT;
		} else {
			const unsigned int idx = obj->count++;
			int error = CBF_SUCCESS;
			if (!(obj->axis_set_id = realloc(obj->axis_set_id,obj->count*sizeof(char*)))) error |= CBF_ALLOC;
			if (!(obj->path = realloc(obj->path,obj->count*sizeof(char*)))) error |= CBF_ALLOC;
			if (!(obj->index = realloc(obj->index,obj->count*sizeof(unsigned int)))) error |= CBF_ALLOC;
			if (!(obj->precedence = realloc(obj->precedence,obj->count*sizeof(unsigned int)))) error |= CBF_ALLOC;
			if (!(obj->dimension = realloc(obj->dimension,obj->count*sizeof(unsigned int)))) error |= CBF_ALLOC;
			if (!(obj->direction = realloc(obj->direction,obj->count*sizeof(char*)))) error |= CBF_ALLOC;
			if (CBF_SUCCESS == error) {
				obj->axis_set_id[idx] = axis_set_id;
				obj->path[idx] = _cbf_strdup(path);
				obj->index[idx] = index;
				obj->precedence[idx] = precedence;
				obj->dimension[idx] = dimension;
				obj->direction[idx] = direction;
			}
			return error;
		}
        }

	static void _cbf_reset_arrayAxisSet(cbf_arrayAxisSet_t * const obj)
	{
		_cbf_free_arrayAxisSet(*obj);
		*obj = _cbf_make_arrayAxisSet();
        }

	/**
	Map an axis ID to an object, a dataset reference, a path to access it and the axis it depends on (or NULL).
	For use in converting goniometer & detector axes.

	Want to be able to partially order the list, with axes grouped by object and sorted by dependency chain.
	Require axis to appear after anything that depends on it, incremental swapping should be stable for acyclic graphs.
	*/
	typedef struct cbf_axis_t {
		/* the name of the axis, which can be used to look up axis data from the CBF axis categories */
		const char * * axis_id;
        
		/* axis path within the HDF5 file, these need free'ing individually */
		const char * * path;
        
		/*
         for use in checking dependency chains & identifying leves,
         in_degree of 0 => leaf axis, default should be 0.
         */
		unsigned int * in_degree;
        
		/*
         index of the axis that this depends on within this structure,
         the default should be a very large value like UINT_MAX.
         */
		unsigned int * depends_on;
        
		unsigned int count;
	} cbf_axis_t;

	static cbf_axis_t _cbf_make_axis()
	{
		cbf_axis_t obj;
		obj.count = 0;
		obj.axis_id = NULL;
		obj.path = NULL;
		obj.in_degree = NULL;
		obj.depends_on = NULL;
		return obj;
    }

	static void _cbf_free_axis(const cbf_axis_t obj)
    {
		const char * const * const path_end = obj.path + obj.count;
		const char * const * p;
		for (p = obj.path; path_end != p; ++p) free((void*)(*p));
		free((void*)obj.axis_id);
		free((void*)obj.path);
		free((void*)obj.in_degree);
		free((void*)obj.depends_on);
	}

	/*
	append an axis entry to the given axis list object, taking ownership of the path iff the function returns successfully.
	*/
	static int _cbf_insert_axis
			(cbf_axis_t * const obj,
			 const char * const axis_id,
     const char * const path)
	{
		if (!obj) {
			return CBF_ARGUMENT;
		} else {
			int error = CBF_SUCCESS;
			const unsigned int idx = obj->count++;
			if (!(obj->axis_id = realloc(obj->axis_id,obj->count*sizeof(char*)))) error |= CBF_ALLOC;
			if (!(obj->path = realloc(obj->path,obj->count*sizeof(char*)))) error |= CBF_ALLOC;
			if (!(obj->in_degree = realloc(obj->in_degree,obj->count*sizeof(unsigned int*)))) error |= CBF_ALLOC;
			if (!(obj->depends_on = realloc(obj->depends_on,obj->count*sizeof(unsigned int*)))) error |= CBF_ALLOC;
			if (CBF_SUCCESS == error) {
				obj->axis_id[idx] = axis_id;
				obj->path[idx] = path;
				obj->in_degree[idx] = 0;
				obj->depends_on[idx] = ~((unsigned int)(0));
			}
			return error;
		}
	}

	static void _cbf_reset_axis(cbf_axis_t * const obj)
	{
		_cbf_free_axis(*obj);
		*obj = _cbf_make_axis();
	}

	/*
	Search the array of strings in 'array' for the first matching 'str'.
	Set the value pointed by 'idx' to the index of the match, or 'size', if it can be dereferenced.
	Return successfully iff a match is found.
	*/
	static int find_index_of_str_in_array
			(const char * const * const array,
			 const size_t size,
			 const char * const str,
			 size_t * const idx)
	{
		int error = CBF_SUCCESS;
		if (!array || !str) {
			error |= CBF_ARGUMENT;
		} else {
			size_t i;
			for (i = 0; size != i; ++i) {
				if (!strcmp(array[i],str)) break;
			}
			if (size==i) error |= CBF_NOTFOUND;
			if (idx) *idx = i;
		}
		return error;
	}

	/**
	Track data describing the current frame/scan that is being converted.
	May be removed once conversion code is more stable, with parameters passed one-by-one to functions.
	*/
	typedef struct cbf_cbf2nx_key_t {
		double matrix [3][3];
		cbf_node * * categories;
		const char * scan;
		const char * frame;
		const char * binary;
		const char * array;
		const char * diffrn;
		const char * diffrn_detector;
		const char * diffrn_detector_element;
		const char * diffrn_measurement;
		const char * wavelength_id;
		const char * data_overload;
		const char * data_undefined;
		const char * detector_dependency;
		const char * goniometer_dependency;
		unsigned int nScans;
		unsigned int nFrames;
		unsigned int frame_number;
		int has_start_time;
		int has_end_time;
		unsigned int indent;
		unsigned int nCat;
		cbf_arrayAxisSet_t arrayAxisSet;
		cbf_axis_t axis;
	} cbf_cbf2nx_key_t;

	static cbf_cbf2nx_key_t _cbf_make_cbf2nx_key()
	{
		cbf_cbf2nx_key_t key;
		key.matrix[0][0] = 0.;
		key.matrix[0][1] = 0.;
		key.matrix[0][2] = 0.;
		key.matrix[1][0] = 0.;
		key.matrix[1][1] = 0.;
		key.matrix[1][2] = 0.;
		key.matrix[2][0] = 0.;
		key.matrix[2][1] = 0.;
		key.matrix[2][2] = 0.;
		key.scan = NULL;
		key.frame = NULL;
		key.binary = NULL;
		key.array = NULL;
		key.diffrn = NULL;
		key.diffrn_detector = NULL;
		key.diffrn_detector_element = NULL;
		key.diffrn_measurement = NULL;
		key.wavelength_id = NULL;
		key.data_overload = NULL;
		key.data_undefined = NULL;
		key.detector_dependency = NULL;
		key.goniometer_dependency = NULL;
		key.nScans = 0;
		key.nFrames = 0;
		key.frame_number = 0;
		key.has_start_time = 0;
		key.has_end_time = 0;
		key.indent = 0;
		key.nCat = 0;
		key.categories = NULL;
		key.arrayAxisSet = _cbf_make_arrayAxisSet();
		key.axis = _cbf_make_axis();
		return key;
    }

	static void _cbf_reset_cbf2nx_key(cbf_cbf2nx_key_t * const key)
	{
		key->frame = NULL;
		key->binary = NULL;
		key->array = NULL;
		key->diffrn = NULL;
		key->diffrn_detector = NULL;
		key->diffrn_detector_element = NULL;
		key->diffrn_measurement = NULL;
		key->wavelength_id = NULL;
		key->data_overload = NULL;
		key->data_undefined = NULL;
		key->detector_dependency = NULL;
		key->goniometer_dependency = NULL;
		key->nFrames = 0;
		key->frame_number = 0;
		key->has_start_time = 0;
		key->has_end_time = 0;
		key->indent = 0;
		_cbf_reset_arrayAxisSet(&key->arrayAxisSet);
		_cbf_reset_axis(&key->axis);
	}

	static void _cbf_free_cbf2nx_key(const cbf_cbf2nx_key_t key)
	{
		_cbf_free_arrayAxisSet(key.arrayAxisSet);
		_cbf_free_axis(key.axis);
	}

	static int _cbf2nx_key_remove_category
    (cbf_cbf2nx_key_t * const key,
     const char * const categoryName)
	{
		int error = CBF_SUCCESS;
		if (!key || !key->categories || !categoryName) {
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * it;
			cbf_node * const * const end = key->nCat+key->categories;
			for (it = key->categories; end != it; ++it) {
				if (*it) {
					*it = strcmp((*it)->name,categoryName) ? *it : NULL;
				}
			}
		}
		return error;
	}
    
	/*
	Some simple 'getters' to access read-only primary key values. C's
	'offsetof' isn't used in order to allow simpler refactoring if keys should
	be stored by column & index instead of directly by value.

	These functions should have a signature compatible with:
	const char * f(const cbf_cbf2nx_key_t *);
	The first parameter is the key to get the value from.
     */
    
	/*
	Many of these are small functions that do almost exactly the same thing, so
	define the implementation in one place so they can be more easily
	maintained.

	-CBF2NX_DECL_KEY_STR_GETTER(FUNC,MEMBER):
		Declares and defines a function 'FUNC' to get the (const char *) value
		of 'key->MEMBER'.
	*/
#define CBF2NX_DECL_KEY_STR_GETTER(FUNC,MEMBER) \
static const char * FUNC \
	(const cbf_cbf2nx_key_t * const key) \
{ \
	if (key) { \
		return key->MEMBER; \
	} else { \
		return NULL; \
	} \
}

	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_array_id,array);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_binary_id,binary);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_scan_id,scan);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_frame_id,frame);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_diffrn_id,diffrn);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_diffrnDetector_id,diffrn_detector);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_diffrnDetectorElement_id,diffrn_detector_element);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_diffrnMeasurement_id,diffrn_measurement);
	CBF2NX_DECL_KEY_STR_GETTER(cbf2nx_key_get_wavelength_id,wavelength_id);

	/*
	Some simple 'setters' to take a string and set a value in the key.

	These functions should have a signature compatible with:
	int f(cbf_cbf2nx_key_t *, const char *);
	The first parameter is the key to store the value in.
	The second parameter is the value to be stored.
	*/

	/*
	Many of these are small functions that do almost exactly the same thing, so
	define the implementation in one place so they can be more easily
	maintained.

	- CBF2NX_DECL_KEY_STR_SETTER(FUNC,MEMBER):
		Declares and defines a function 'FUNC' to set the (const char *) value
		of 'key->MEMBER'.
	*/
#define CBF2NX_DECL_KEY_STR_SETTER(FUNC,MEMBER) \
static int FUNC \
		(cbf_cbf2nx_key_t * const key, \
		const char * const value) \
{ \
	int error = CBF_SUCCESS; \
	if (!key || !value) { \
		error |= CBF_ARGUMENT; \
	} else { \
		key->MEMBER = value; \
	} \
	return error; \
}

	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_diffrn,diffrn);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_diffrn_detector,diffrn_detector);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_diffrn_measurement,diffrn_measurement);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_array,array);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_binary,binary);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_overload,data_overload);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_undefined,data_undefined);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_diffrn_detector_element,diffrn_detector_element);
	CBF2NX_DECL_KEY_STR_SETTER(cbf2nx_key_set_wavelength_id,wavelength_id);

	/*
	Function to set the (unsigned integer) value of 'key->frame_number'.
	*/
	static int cbf2nx_key_set_frame_number
			(cbf_cbf2nx_key_t * const key,
			 const char * const value)
	{
		int error = CBF_SUCCESS;
		if (!key || !value) {
			error |= CBF_ARGUMENT;
		} else {
			char * end;
			unsigned int frame_number = strtoull(value,&end,10);
			if (end!=value)
				key->frame_number = frame_number;
			else
				error |= CBF_FORMAT;
		}
		return error;
	}

    /****************************************************************
     The following section of code is extracted from J. Sloan's
     cbf_hdf5.i
     ****************************************************************/

    /*
     Some comparison functions for use in checking the content of
     HDF5 datasets/attributes

     Should return 0 on success, non-zero on failure
     */
/* We provide a macro and 2 versions of each of the calls with _ULP
     variants. */
    
#ifdef CBF_USE_ULP
#define CBFM_cmp_double(exp,ext,len,prm) cmp_double(exp,ext,len,prm)
#define CBFM_cmp_int(exp,ext,len,prm) cmp_int(exp,ext,len,prm)
#define CBFM_cmp_vlstring(exp,ext,len,prm) cmp_vlstring(exp,ext,len,prm)
#else
#define CBFM_cmp_double(exp,ext,len,prm) cmp_double(exp,ext,len)
#define CBFM_cmp_int(exp,ext,len,prm) cmp_int(exp,ext,len)
#define CBFM_cmp_vlstring(exp,ext,len,prm) cmp_vlstring(exp,ext,len)
#endif

#ifdef CBF_USE_ULP
	typedef struct cmp_double_param_t {
		int cmp_double_as_float; /* do I use the 64 bit version, if available? */
		unsigned int ulp32; /* 32-bit comparison parameter */
#ifndef NO_UINT64_TYPE
		uint64_t ulp64; /* 64-bit comparison parameter */
#endif
	} cmp_double_param_t;

	/** Compare two vectors of doubles */
	static int cmp_double(const void * const expected, const void * const existing, 
                          size_t length, const void * const params)
    {
		const cmp_double_param_t * const cmp_params = (cmp_double_param_t*)(params);
		const double * A = expected;
		const double * B = existing;

        /* go through each vector comparing all values */
#ifndef NO_UINT64_TYPE
		if (!cmp_params->cmp_double_as_float && cbf_has_ULP64()) {
			while (length && cbf_ULP64(*A++, *B++) < cmp_params->ulp64) --length;
		}
		else
#endif
		{
			while (length && cbf_ULP32(*A++, *B++) < cmp_params->ulp32) --length;
		}
		/* if any are not equal the loop will exit early and length is non-zero */
        return length;
    }
#else
    static int cmp_double(const void * a, const void * b, size_t N)
    {
        /* go through each vector comparing all values
         The allowed delta is 1.e-38+1.e-13*maxmimum of the
         summed pairs of absolute values
         */

        double delta = 0.;
        const double * da = a;
        const double * db = b;

        size_t i;

        for (i=0; i < N; i++) {
            if (fabs(da[i])+fabs(db[i]) > delta) delta = fabs(da[i])+fabs(db[i]);
            if (fabs(da[i]-db[i]) > 1.e-38+1.e-13*delta) return 1;
        }

        for (i=0; i < N-1; i++) {
            if (fabs(da[i]-da[i]) > 1.e-38+1.e-13*delta) return 1;
        }

        return 0;
    }
#endif

#ifdef CBF_USE_ULP
    static int cmp_int(const void * const expected,
                       const void * const existing,
                       size_t length,
                       const void * const params)
#else
    static int cmp_int(const void * const expected,
                       const void * const existing,
                       size_t length)
#endif
    {
		const int * A = expected;
		const int * B = existing;
        
		/* go through each vector comparing all values */
		while (length && *A++ == *B++) --length;
		/* if any are not equal the loop will exit early and length is non-zero */
		return length;
    }

#ifdef CBF_USE_ULP
    static int cmp_vlstring(const void * a, const void * b, size_t N, 
      const void * const params)
#else
    static int cmp_vlstring(const void * a, const void * b, size_t N)
#endif
    {
        const char * const * A = a;
		const char * const * B = b;
        
        /* go through each vector comparing all values */
        while (N && !cbf_cistrcmp(*A++, *B++)) --N;
        /* if any are not equal the loop will exit early and N is non-zero */
        return N;
    }

	/**
     Put a character into a buffer at a given position.

     Ensures the buffer is long enough to hold the new character, realloc'ing if needed, and then inserts it.

     \param c The character.
     \param buf A pointer to the realloc'able buffer.
     \param n A pointer to the current length of the buffer.
     \param k The offset to place the character <code>c</code> in.

     \return void
	 */
	void cbf_push_buf(const int c, char * * const buf, size_t * const n, size_t *k)
	{
        int errorcode=0;
        size_t old_nelem;
		assert(buf);
		assert(n);
		assert(k);
        old_nelem = *n;
		if (*k >= *n) {
			*n = 1+2 * (*k);
            errorcode = cbf_realloc((void **)buf, &old_nelem, 1, *n);
		}
        if (!errorcode) {
		  (*buf)[(*k)++] = c;
        }
	}

	/**
     Function to tokenise a pilatus v1.2 minicbf header

     Will split the header into null-terminated strings that are passed around via a given realloc'able buffer.

     Behviour is determined by <code>newline</code>, if <code>newline</code> is non-zero:
     A token starting with a digit, <code>[0-9]</code>, will cause a string consisting of digits
     and any number or combination of <code>[T:-.]</code> characters to be matched as a token.
     Otherwise, the stream will be tokenised according to the default rules.

     The default tokenisation method is to split the stream on groups of characters from the set <code>[#=:,() \t\f\v\r\n]</code>.
     Any number of adjacent <code>'\r'</code> and <code>'\n'</code> characters are compressed into a single
     newline (<code>"\n"</code>) token.
	 */
	static int _cbf_scan_pilatus_V1_2_miniheader
    (char * * const buf,
     size_t * const n,
     int * const newline,
     const int getRestOfLine,
     const char * * const string)
	{
#define cbf_sgetc(str) (**str ? *(*str)++ : 0)
#define cbf_seof(str) (!**str)
#define cbf_ungetc(str) (--(*str))
		int c = 0; /* current character */
		size_t k = 0; /* current line length */
		const char spaceChars[] = "#=:,() \t\f\v";
		const char newlineChars[] = "\n\r";

		/* check that sensible arguments are given */
		assert(buf);
		assert(n);
		assert(newline);
		assert(string);

		/*
         Skip space-equivalent characters to find something interesting.
         This ends with one of two states: a non-space character is found, or EOF.
         */
		do {
			c = cbf_sgetc(string);
			if (cbf_seof(string)) break;
			if (strchr(spaceChars,c)) continue;
			else break;
		} while (1);

		/* if I am at the end of the stream, free the buffer & return 0 */
		if (cbf_seof(string)) {
			free((void*)(*buf));
			*buf = 0;
			*n = 0;
			return CBF_SUCCESS;
		}

		/* I have a token, starting with the character c: read it */
		if (strchr(newlineChars,c)) {
			/* it's a newline token: consume all consecutive newline-equivalent characters */
			do {
				c = cbf_sgetc(string);
			} while (!cbf_seof(string) && strchr(newlineChars,c));
			if (!cbf_seof(string)) cbf_ungetc(string);
			cbf_push_buf('\n', buf, n, &k);
			*newline = 1;
		} else {
			/* It's a string token */
			if (getRestOfLine || (*newline && isdigit(c))) {
				/* scan to the end of the current line */
				do {
					cbf_push_buf(c, buf, n, &k);
					c = cbf_sgetc(string);
				} while (!cbf_seof(string) && !strchr(newlineChars,c));
				if (!cbf_seof(string)) cbf_ungetc(string);
			} else {
				/* scan it as an arbitrary token */
				do {
					cbf_push_buf(c, buf, n, &k);
					c = cbf_sgetc(string);
				} while (!cbf_seof(string) && !strchr(spaceChars,c) && !strchr(newlineChars,c));
				if (!cbf_seof(string)) cbf_ungetc(string);
			}
			*newline = 0;
		}
		/* null-terminate the token */
		cbf_push_buf('\0', buf, n, &k);

		return CBF_SUCCESS;
	}

	/**
     Helper function to check if a string is a valid (pilatus format) null-terminated date.

     Requires string of format:
     <code>YYYY-MM-DDThh:mm:ss.s+</code>
     <code>Y</code>: year
     <code>M</code>: month
     <code>D</code>: day
     <code>h</code>: hour
     <code>m</code>: minute
     <code>s</code>: second
     <code>+</code>: second may be fractional, any number of digits are allowed
     <code>[-T:]</code>: literal characters

     \param str The string to test.

     \return non-zero on success, zero otherwise.
	 */
	static int isDateTime(const char * str)
	{
		if (!str) return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if ('-'==*str) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if ('-'==*str) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if ('T'==*str) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (':'==*str) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (':'==*str) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		if (isdigit(*str)) ++str; else return 0;
		/* Optional '.s*' (fractional second) component: */
		if ('.'==*str) ++str; else return '\0'==*str;
		while (isdigit(*str)) ++str;
		return '\0'==*str;
	}


    /****************************************************************
     The following section of code is extracted from J. Sloan's
     cbf_hdf5_common.c
     ****************************************************************/


	/**
     Function to check validity of a HDF5 identifier.
     HDF5's predefined types are never counted as valid by this function,
     so it can't be used to test the validity of a type constant.
     Types obtained by using H5Tcopy are safe to test.

     \param ID An HDF5 object identifier.
     \sa cbf_H5Ocmp
     \return Non-zero if the type is valid, zero otherwise.
     */
	int cbf_H5Ivalid(const hid_t ID)
	{
		const htri_t v = H5Iis_valid(ID);
		if (v < 0) {
            cbf_debug_print("H5Iis_valid call failed.\n");
        }
		return v > 0;
	}

	/*
	find/create/free a HDF5 group if it's valid & possibly set the ID to an invalid identifier.
     */

	/**
	<p>Helper function to attempt to create a HDF5 group identified by <code>name</code> and return an error
	code, to make error handling more consistant. This will fail if a link with the same name already exists
	in <code>parent</code>.</p>

	\param location The group that will contain the newly created group.
     \param group A pointer to a HDF5 ID type where the group will be stored.
     \param name The name that the group will be given.
     \sa cbf_H5Gcreate
     \sa cbf_H5Gfind
     \sa cbf_H5Grequire
     \sa cbf_H5Gfree
     \return An error code.
     */
	int cbf_H5Gcreate(const hid_t location, hid_t * const group, const char * const name)
	{
		if (!group || !name || !cbf_H5Ivalid(location)) return CBF_ARGUMENT;

		/* check if the link exists */
		const htri_t l = H5Lexists(location, name, H5P_DEFAULT);
		if (l < 0) return CBF_H5ERROR;
		else if (!l) {
			/* no group exists: try to create it */
			*group = H5Gcreate2(location,name,H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
			return cbf_H5Ivalid(*group) ? CBF_SUCCESS : CBF_H5ERROR;
		} else {
			/* something exists, hence I can't *create* anything: error */
            cbf_debug_print2("A link of the same name, '%s', already exists\n",name)
			return CBF_H5ERROR;
		}
	}

	/**
     <p>Checks for the existance of a group with the given <code>name</code> and <code>parent</code>. Will return
     <code>CBF_NOTFOUND</code> if it cannot be found, or open it if it already exists. An error code will be
     returned if something other than a group exists at the specified location.</p>

     \param location The group to be searched.
     \param group A pointer to a HDF5 ID type where the group will be stored.
     \param name The path (ie, name) of the group to be found.
     \sa cbf_H5Gcreate
     \sa cbf_H5Gfind
     \sa cbf_H5Grequire
     \sa cbf_H5Gfree
     \return An error code.
     */
	int cbf_H5Gfind(const hid_t location, hid_t * const group, const char * const name)
	{
		/* check the arguments */
		if (!group || !name || !cbf_H5Ivalid(location)) return CBF_ARGUMENT;
        
		/* check if the link exists */
		const htri_t l = H5Lexists(location, name, H5P_DEFAULT);
		if (l < 0) return CBF_H5ERROR;
		else if (!l) {
			/* no group exists */
			return CBF_NOTFOUND;
		} else {
			/* something exists, check what it is */
			const htri_t e = H5Oexists_by_name(location, name, H5P_DEFAULT);
			if (e < 0) return CBF_H5ERROR;
			else if (!e) {
				/* The link exists but the object doesn't - remove the link & return */
				if (H5Ldelete(location, name, H5P_DEFAULT) < 0) return CBF_H5ERROR;
				else return CBF_NOTFOUND;
			} else {
				/* my object exists - check its type */
				hid_t g = H5Oopen(location, name, H5P_DEFAULT);
				if (H5I_GROUP == H5Iget_type(g)) {
					/* it's a group - return it */
					*group = g;
					return CBF_SUCCESS;
				} else {
					/* not a group - close the object & fail */
					H5Oclose(g);
					return CBF_H5DIFFERENT;
				}
			}
		}
	}
    
	/**
	<p>Checks for the existance of a group with the given <code>name</code> and <code>parent</code>. Will create the
	group if it cannot be found, or open it if it already exists. It is an error if a matching group cannot be found or
	created. This uses <code>cbf_H5Gcreate</code> to create any new groups.</p>

	\param location The group that will contain the newly created group.
     \param group A pointer to a HDF5 ID type where the group will be stored.
     \param name The name that the group will be given.
     \sa cbf_H5Gcreate
     \sa cbf_H5Gfind
     \sa cbf_H5Grequire
     \sa cbf_H5Gfree
     \return An error code.
     */
	int cbf_H5Grequire(const hid_t location, hid_t * const group, const char * const name)
	{
		/* check the arguments */
		if (!group || !name || !cbf_H5Ivalid(location)) return CBF_ARGUMENT;

		/* check if the link exists */
		const htri_t l = H5Lexists(location, name, H5P_DEFAULT);
		if (l < 0) return CBF_H5ERROR;
		else if (!l) {
			/* no group exists: try to create it */
			return cbf_H5Gcreate(location,group,name);
		} else {
			/* something exists, check what it is */
			const htri_t e = H5Oexists_by_name(location, name, H5P_DEFAULT);
			if (e < 0) return CBF_H5ERROR;
			else if (!e) {
				/* The link exists but the object doesn't - remove the link & create the object */
				if (H5Ldelete(location, name, H5P_DEFAULT) < 0) return CBF_H5ERROR;
				else {
					return cbf_H5Gcreate(location,group,name);
				}
			} else {
				/* my object exists - check its type */
				hid_t g = H5Oopen(location, name, H5P_DEFAULT);
				if (H5I_GROUP == H5Iget_type(g)) {
					/* it's a group - return it */
					*group = g;
					return CBF_SUCCESS;
				} else {
					/* not a group - close the object & fail */
					H5Oclose(g);
					return CBF_H5DIFFERENT;
				}
			}
		}
	}

    /**
     Attempt to close a group, but don't modify the identifier that described it.

     \param ID The HDF5 group to be closed.
     \sa cbf_H5Gcreate
     \sa cbf_H5Gfind
     \sa cbf_H5Grequire
     \sa cbf_H5Gfree
     \return An error code.
     */
	int cbf_H5Gfree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Gclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}

	/* Open/close a HDF5 file if it's valid & possibly set the ID to an invalid identifier - deliberately avoid find/create/free or
     get/set/clear naming convensions */

	/**
	<p>Will try to open a file of the given name with suitable values for some of it's properties to make memory leaks
	less likely.</p>

	<p><em>Warning:</em> this function will destroy any existing data in the file, do not pass the name of any file
	containing data you want to keep.</p>

     \param file A pointer to an HDF5 ID where the newly opened file should be stored.
     \param name The name of the file to attempt to open.
     \sa cbf_H5Fopen
     \sa cbf_H5Fclose
     \return An error code.
     */
	int cbf_H5Fopen(hid_t * const file, const char * const name)
	{
		/* define variables & check args */
		int error = CBF_SUCCESS;
		if (!file || !name) {
			error |= CBF_ARGUMENT;
		} else {
		hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
			if (!cbf_H5Ivalid(fapl)) {
                cbf_debug_print("error, couldn't create file access property list.\n");
				error |= CBF_H5ERROR;
			} else {
				CBF_H5CALL(H5Pset_fclose_degree(fapl,H5F_CLOSE_STRONG));
		/*
                 in H5Fcreate:
                 - H5F_ACC_TRUNC:
			overwrites any previous file, losing any existing data
                 - H5F_ACC_EXCL:
			fail if the file already exists, so data isn't lost
                 can then fall back to H5Fopen to try to open the existing file safely
		*/
				CBF_H5CALL(*file = H5Fcreate(name,H5F_ACC_TRUNC,H5P_DEFAULT,fapl));
			}
		if (cbf_H5Ivalid(fapl)) H5Pclose(fapl);
		}
		return error;
	}

	/**
     Attempt to close a file, but don't modify the identifier that described it.

     \param ID The HDF5 file to be closed.
     \sa cbf_H5Fopen
     \sa cbf_H5Fclose
     \return An error code.
     */
	int cbf_H5Fclose(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Fclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}

	/* Attributes */
    
	/**
     Creates a new attribute of the object <code>location</code> with name given by <code>name</code>,
     optionally returning it in the <code>attr</code> variable. An error will occur if a similarly
     named attribute already exists.
     
     \param location The hdf5 group/file in which to put the attribute.
     \param attr A pointer to a HDF5 object identifier that is set to the location of a valid object
     if the function succeeds, otherwise is left untouched.
     \param name The name of the existing/new dataset.
     \param type The type of data to be stored in the attribute.
     \param space The dataspace of the attribute.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Acreate
    (const hid_t location,
     hid_t * const attr,
     const char * const name,
     const hid_t type,
     const hid_t space)
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(location)
            || !attr
            || !name
            || H5I_DATATYPE!=H5Iget_type(type)
            || !cbf_H5Ivalid(space)
            ) error |= CBF_ARGUMENT;
		if (CBF_SUCCESS==error) {
			const htri_t exists = H5Aexists(location,name);
			if (exists<0) {
				error |= CBF_H5ERROR;
			} else if (exists<=0) {
				const hid_t attribute = H5Acreate2(location, name, type, space, H5P_DEFAULT, H5P_DEFAULT);
				if (attribute>=0) *attr = attribute;
				else error |= CBF_H5ERROR;
			} else {
                cbf_debug_print2("attribute '%s' exists\n",name);
				error |= CBF_IDENTICAL;
			}
		}
		return error;
	}
    
	/**
     Checks for the existance of an attribute with the given <code>name</code> at <code>location</code>
     with a datatype of <code>type</code> and dataspace of <code>space</code>. Will return
     <code>CBF_NOTFOUND</code> if it cannot be found, or open it if it already exists.
     
     If <code>type</code> is not a datatype then no check of the attribute datatype will be done.
     If <code>space</code> is not a dataspace then no checks of the attribute dataspace wil be done.
     
     \param location The hdf5 group/file in which to put the attribute.
     \param attr A pointer to a HDF5 object identifier that is set to the location of a valid object
     if the function succeeds, otherwise is left untouched.
     \param name The name of the existing/new attribute.
     \param type The type of data stored in the attribute, or an invalid identifier if it should not be checked.
     \param space The dataspace of the attribute, or an invalid identifier if it should not be checked.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Afind
    (const hid_t location,
     hid_t * const attr,
     const char * const name,
     const hid_t type,
     const hid_t space)
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(location) || !attr || !name) {
			/* type & space should not be checked here, they are optional */
			error |= CBF_ARGUMENT;
		} else {
			const htri_t exists = H5Aexists(location,name);
			if (exists<0) {
				error |= CBF_H5ERROR;
			} else if (!exists) {
				cbf_debug_print2("attribute '%s' doesn't exist\n",name);
				error |= CBF_NOTFOUND;
			} else {
				hid_t attribute = H5Aopen(location,name,H5P_DEFAULT);
				if (attribute<0) {
					cbf_debug_print2("could not open '%s' attribute\n",name);
					error |= CBF_H5ERROR;
				} else {
					/* get the datatype */
					const hid_t currType = H5Aget_type(attribute);
					const hid_t currSpace = H5Aget_space(attribute);
					if (!(cbf_H5Ivalid(currType) && cbf_H5Ivalid(currSpace))) {
						cbf_debug_print2("could not get type or space of '%s' attribute\n",name);
						error |= CBF_H5ERROR;
					} else {
						if (H5I_DATATYPE==H5Iget_type(type)) {
							/* check the datatype is correct */
							const htri_t eq = H5Tequal(currType,type);
							if (eq<0) error |= CBF_H5ERROR;
							else if (!eq) error |= CBF_H5DIFFERENT;
						}
						if (H5I_DATASPACE==H5Iget_type(space)) {
							/* check the dataspace is correct */
							const htri_t eq = H5Sextent_equal(currSpace,space);
							if (eq<0) error |= CBF_H5ERROR;
							else if (!eq) error |= CBF_H5DIFFERENT;
						}
						if (CBF_SUCCESS==error) {
							*attr = attribute;
							attribute = CBF_H5FAIL;
						}
					}
					cbf_H5Tfree(currType);
					cbf_H5Sfree(currSpace);
				}
				cbf_H5Afree(attribute);
			}
		}
		return error;
	}
    
	/**
     Reads all of the data from <code>attr</code> into <code>buf</code>, which should have been
     allocated as the native type indicated by <code>mem_type</code>.
     
     \param attr A valid hdf5 handle for an attribute.
     \param type The type of data in memory.
     \param buf The location where the data is to be stored.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Aread
    (const hid_t attr,
     const hid_t type,
     void * const buf)
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(attr) || H5I_DATATYPE!=H5Iget_type(type) || !buf) {
			error |= CBF_ARGUMENT;
		} else {
			if (H5Aread(attr,type,buf)<0) {
				cbf_debug_print("couldn't read attribute\n");
				error |= CBF_H5ERROR;
			}
		}
		return error;
	}
    
	/**
     Read a string attribute into memory, returning a pointer that must be free'd by the caller
     in <code>val</code>.
     
     \param attr The attribute to read from.
     \param val A pointer to a place the string may be stored.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Aread_string
    (const hid_t attr,
     const char * * const val)
	{
		/*
         TODO: tests
         */
		int error = CBF_SUCCESS;
		hid_t ftype = CBF_H5FAIL;
		hid_t space = CBF_H5FAIL;
		hssize_t points = -1;
		if (!cbf_H5Ivalid(attr) || !val) error |= CBF_ARGUMENT;
		if ((ftype=H5Aget_type(attr))<0) {
			cbf_debug_print(" couldn't get type of attribute\n");
			error |= CBF_H5ERROR;
		} else if (H5T_STRING!=H5Tget_class(ftype)) {
			cbf_debug_print("wrong type class for attribute\n");
			error |= CBF_H5DIFFERENT;
		} else if ((space=H5Aget_space(attr))<0) {
			cbf_debug_print("couldn't get space of attribute\n");
			error |= CBF_H5ERROR;
		} else if ((points=H5Sget_simple_extent_npoints(space))<0) {
			cbf_debug_print("couldn't get number of datapoints\n");
			error |= CBF_H5ERROR;
		} else if (1!=points) {
			cbf_debug_print("unexpected number of datapoints\n");
			error |= CBF_H5DIFFERENT;
		} else {
			hid_t mtype = CBF_H5FAIL;
			char * value = NULL;
			void * ptr = NULL;
			if (H5Tis_variable_str(ftype)) {
				error |= cbf_H5Tcreate_string(&mtype, H5T_VARIABLE);
				ptr = &value;
			} else {
				const size_t size = H5Tget_size(ftype);
				error |= cbf_H5Tcreate_string(&mtype, size);
				value = malloc(1+size);
				ptr = value;
			}
			if (CBF_SUCCESS!=error) {
				cbf_debug_print("couldn't create string datatype\n");
			} else if (H5Aread(attr, mtype, ptr)<0) {
				cbf_debug_print("could not read attribute\n");
				error |= CBF_H5ERROR;
			} else {
				*val = value;
			}
			cbf_H5Tfree(mtype);
		}
		cbf_H5Tfree(ftype);
		return error;
	}
    
	/**
     Writes all of the data from <code>buf</code>, which should contain data if the type
     indicated by <code>mem_type</code>, into <code>attr</code>.
     
     \param attr A valid hdf5 handle for an attribute.
     \param type The type of data in memory.
     \param buf The address of the data to be written.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Awrite
    (const hid_t attr,
     const hid_t type,
     void * const buf)
	{
		return CBF_NOTIMPLEMENTED;
	}
    
    /* \brief Check for an attribute with the given space/type/value, or set one if it doesn't exist.
     
     Checks the existance of an attribute of the given name, creating it if it doesn't exist.
     
     Checks the size, type and value of an existing attribute to find out if it is the same as
     what was requested as determined by a custom comparison function which may use some extra data
     for more sophisticated tests.
     
     \param ID The HDF5 object that the attribute will be applied to.
     \param name The name of the attribute.
     \param rank The number of dimensions of the attribute data, 0 for scalar data.
     \param dim The length of each dimension, not used for scalar data.
     \param type The HDF5 type of the attribute data.
     \param value The data to be written to the attribute.
     \param buf A buffer to be used when reading an existing attribute of the same size.
     \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
     
     \sa cbf_H5Arequire_string
     
     \return An error code.
     */
	int cbf_H5Arequire_cmp
    (const hid_t ID,
     const char * const name,
     const int rank,
     const hsize_t * const dim,
     const hid_t attrType,
     const void * const value,
     void * const buf,
     int (*cmp)(const void * a, const void * b, size_t N))
	{
		/* define variables & check args */
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(ID) || !name || (rank && !dim) || rank<0) {
			error |= CBF_ARGUMENT;
		} else {
		hid_t attrSpace = CBF_H5FAIL;
			if (CBF_SUCCESS != (error|=cbf_H5Screate(&attrSpace, rank, dim, 0))) {
				cbf_debug_print("error: couldn't create data space");
			} else {
		if (H5Aexists(ID,name)>0) {
			hid_t attr = H5Aopen(ID,name,H5P_DEFAULT);
			hid_t currSpace = H5Aget_space(attr);
			hid_t currType = H5Aget_type(attr);
			/* check everything was opened properly */
			if (!cbf_H5Ivalid(attr)) error |= CBF_H5ERROR;
			if (!cbf_H5Ivalid(currSpace)) error |= CBF_H5ERROR;
			if (!cbf_H5Ivalid(currType)) error |= CBF_H5ERROR;
			if (CBF_SUCCESS==error) {
                /* check that the dataspace is correct */
				const htri_t eq = H5Sextent_equal(currSpace,attrSpace);
				if (eq<0) error |= CBF_H5ERROR;
				else if (!eq) error |= CBF_H5DIFFERENT;
				else /* success */;
			}
			if (CBF_SUCCESS==error) {
                /* check the datatype is correct */
				const htri_t eq = H5Tequal(currType,attrType);
				if (eq<0) error |= CBF_H5ERROR;
				else if (!eq) error |= CBF_H5DIFFERENT;
				else /* success */;
			}
			/* check that the data is correct */
			if (CBF_SUCCESS==error) {
				const size_t N = H5Sget_simple_extent_npoints(currSpace);
				const size_t vlStr = H5Tis_variable_str(currType);
				H5Aread(attr,attrType,buf);
                        if (cmp(value,buf,N)) {
                            cbf_debug_print("Incorrect attribute value\n");
                    error |= CBF_H5DIFFERENT;
                }
				if (vlStr < 0) error |= CBF_H5ERROR;
				if (vlStr > 0) H5Dvlen_reclaim(currType, currSpace, H5P_DEFAULT, buf);
            }
			/* check local variables are properly closed */
			if (cbf_H5Ivalid(currSpace))  H5Sclose(currSpace);
			if (cbf_H5Ivalid(currType))  H5Tclose(currType);
					if (cbf_H5Ivalid(attr)) H5Aclose(attr);
		} else {
					hid_t attr = CBF_H5FAIL;
					CBF_H5CALL(attr = H5Acreate2(ID,name,attrType,attrSpace,H5P_DEFAULT,H5P_DEFAULT));
					CBF_H5CALL(H5Awrite(attr,attrType,value));
		}
				H5Sclose(attrSpace);
			}
		}
		return error;
	}


	/**
     Checks the existance of an attribute of the given name, size, type and value. Equal value is determined by a
	custom comparison function which may use some extra data for more sophisticated tests. A new attribute with the
	given properties will be created if none currently exist, the function will fail if an incompatible attribute
     exists.

     \param ID The HDF5 object that the attribute will be applied to.
     \param name The name of the attribute.
     \param rank The number of dimensions of the attribute data, 0 for scalar data.
     \param dim The length of each dimension, not used for scalar data.
	\param fileType The HDF5 type of the attribute data in the file.
	\param memType The HDF5 type of the attribute data in memory.
     \param value The data to be written to the attribute.
     \param buf A buffer to be used when reading an existing attribute of the same size.
     \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Arequire_cmp2
    (const hid_t ID,
     const char * const name,
     const int rank,
     const hsize_t * const dim,
	 const hid_t fileType,
	 const hid_t memType,
     const void * const value,
     void * const buf,
	 int (*cmp)(const void *, const void *, size_t))
	{
		/* define variables & check args */
		int error = CBF_SUCCESS;
		hid_t attrSpace = CBF_H5FAIL;
		hid_t attr = CBF_H5FAIL;
		if (!cbf_H5Ivalid(ID)) error |= CBF_ARGUMENT;
		if (!name || (rank && !dim) || rank<0) error |= CBF_ARGUMENT;
		if (H5I_DATATYPE!=H5Iget_type(fileType)) error |= CBF_ARGUMENT;
		if (H5I_DATATYPE!=H5Iget_type(memType)) error |= CBF_ARGUMENT;
		if (!value) error |= CBF_ARGUMENT;
		cbf_reportFail(cbf_H5Screate(&attrSpace, rank, dim, 0), error);

		/* do some work */
		if (CBF_SUCCESS==error) {
		if (H5Aexists(ID,name) > 0) {
			hid_t attr = H5Aopen(ID,name,H5P_DEFAULT);
			hid_t currSpace = H5Aget_space(attr);
			hid_t currType = H5Aget_type(attr);
			/* check everything was opened properly */
			if (!cbf_H5Ivalid(attr)) error |= CBF_H5ERROR;
			if (!cbf_H5Ivalid(currSpace)) error |= CBF_H5ERROR;
			if (!cbf_H5Ivalid(currType)) error |= CBF_H5ERROR;
			if (CBF_SUCCESS==error) {
                /* check that the dataspace is correct */
				const htri_t eq = H5Sextent_equal(currSpace,attrSpace);
				if (eq<0) error |= CBF_H5ERROR;
				else if (!eq) error |= CBF_H5DIFFERENT;
				else /* success */;
			}
			if (CBF_SUCCESS==error) {
                /* check the datatype is correct */
					const htri_t eq = H5Tequal(currType,fileType);
				if (eq<0) error |= CBF_H5ERROR;
				else if (!eq) error |= CBF_H5DIFFERENT;
				else /* success */;
			}
			/* check that the data is correct */
			if (CBF_SUCCESS==error) {
				const size_t N = H5Sget_simple_extent_npoints(currSpace);
				const size_t vlStr = H5Tis_variable_str(currType);
					void * const _buf = buf ? 0 : malloc(H5Sget_simple_extent_npoints(currSpace)*H5Tget_size(currType));
					void * const membuf = buf ? buf : _buf;
					H5Aread(attr,memType,membuf);
					if (cmp(value,membuf,N)) {
						cbf_debug_print("Incorrect attribute value\n");
                    error |= CBF_H5DIFFERENT;
                }
				if (vlStr < 0) error |= CBF_H5ERROR;
					if (vlStr > 0) H5Dvlen_reclaim(currType, currSpace, H5P_DEFAULT, membuf);
					free(_buf);
            }
			/* check local variables are properly closed */
				cbf_H5Sfree(currSpace);
				cbf_H5Tfree(currType);
		} else {
				reportFail(cbf_H5Ivalid(attr = H5Acreate2(ID,name,fileType,attrSpace,H5P_DEFAULT,H5P_DEFAULT)), CBF_H5ERROR, error);
				reportFail(H5Awrite(attr,memType,value)>=0, CBF_H5ERROR, error);
			}
		}

		/* check local variables are properly closed */
		if (cbf_H5Ivalid(attrSpace))  H5Sclose(attrSpace);
		if (cbf_H5Ivalid(attr))  H5Aclose(attr);

		/* done */
		return error;
	}

        
        /** \brief Check for an attribute with the given space/type/value, or set one if it doesn't exist.
         
         <p>Checks the existance of an attribute of the given name, size, type and value. Equal value is determined by a
         custom comparison function which may use some extra data for more sophisticated tests. A new attribute with the
         given properties will be created if none currently exist, the function will fail if an incompatible attribute
         exists.</p>
         
         \param ID The HDF5 object that the attribute will be applied to.
         \param name The name of the attribute.
         \param rank The number of dimensions of the attribute data, 0 for scalar data.
         \param dim The length of each dimension, not used for scalar data.
         \param fileType The HDF5 type of the attribute data in the file.
         \param memType The HDF5 type of the attribute data in memory.
         \param value The data to be written to the attribute.
         \param buf A buffer to be used when reading an existing attribute of the same size.
         \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
         \param cmp_params A pointer to a data structure which may be used by the comparison function.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
         \return An error code.
         */
        int cbf_H5Arequire_cmp2_ULP
        (const hid_t ID,
         const char * const name,
         const int rank,
         const hsize_t * const dim,
         const hid_t fileType,
         const hid_t memType,
         const void * const value,
         void * const buf,
         int (*cmp)(const void *, const void *, size_t, const void *),
         const void * const cmp_params)
        {
            /* define variables & check args */
            int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(ID) || !name || (rank && !dim) || rank<0 || H5I_DATATYPE!=H5Iget_type(fileType) || H5I_DATATYPE!=H5Iget_type(memType) || !value) {
			error |= CBF_ARGUMENT;
		} else {
            hid_t attrSpace = CBF_H5FAIL;
			if (CBF_SUCCESS != (error|=cbf_H5Screate(&attrSpace, rank, dim, 0))) {
				cbf_debug_print("error: couldn't create data space");
			} else {
                if (H5Aexists(ID,name) > 0) {
                    hid_t attr = H5Aopen(ID,name,H5P_DEFAULT);
                    hid_t currSpace = H5Aget_space(attr);
                    hid_t currType = H5Aget_type(attr);
                    /* check everything was opened properly */
                    if (!cbf_H5Ivalid(attr)) error |= CBF_H5ERROR;
                    if (!cbf_H5Ivalid(currSpace)) error |= CBF_H5ERROR;
                    if (!cbf_H5Ivalid(currType)) error |= CBF_H5ERROR;
                    if (CBF_SUCCESS==error) {
                        /* check that the dataspace is correct */
                        const htri_t eq = H5Sextent_equal(currSpace,attrSpace);
                        if (eq<0) error |= CBF_H5ERROR;
                        else if (!eq) error |= CBF_H5DIFFERENT;
                        else /* success */;
                    }
                    if (CBF_SUCCESS==error) {
                        /* check the datatype is correct */
                        const htri_t eq = H5Tequal(currType,fileType);
                        if (eq<0) error |= CBF_H5ERROR;
                        else if (!eq) error |= CBF_H5DIFFERENT;
                        else /* success */;
                    }
                    /* check that the data is correct */
                    if (CBF_SUCCESS==error) {
                        const size_t N = H5Sget_simple_extent_npoints(currSpace);
                        const size_t vlStr = H5Tis_variable_str(currType);
                        void * const _buf = buf ? 0 : malloc(H5Sget_simple_extent_npoints(currSpace)*H5Tget_size(currType));
                        void * const membuf = buf ? buf : _buf;
                        H5Aread(attr,memType,membuf);
                        if (cmp(value,membuf,N,cmp_params)) {
                            cbf_debug_print("Incorrect attribute value\n");
                                error |= CBF_H5DIFFERENT;
                            }
                            if (vlStr < 0) error |= CBF_H5ERROR;
                            if (vlStr > 0) H5Dvlen_reclaim(currType, currSpace, H5P_DEFAULT, membuf);
                            free(_buf);
                        }
                        /* check local variables are properly closed */
                        cbf_H5Sfree(currSpace);
                        cbf_H5Tfree(currType);
					cbf_H5Afree(attr);
                    } else {
					hid_t attr = CBF_H5FAIL;
					CBF_H5CALL(attr = H5Acreate2(ID,name,fileType,attrSpace,H5P_DEFAULT,H5P_DEFAULT));
					CBF_H5CALL(H5Awrite(attr,memType,value));
					cbf_H5Afree(attr);
                    }
				H5Sclose(attrSpace);
                }
		}
                return error;
            }

    static int cmp_string(const void * const a, const void * const b, const size_t N
#ifdef CBF_USE_ULP
                , const void * const params
#endif
    )
	{
		if (1 != N) return 1;
		else return strcmp(a,b);
	}

	/**
     Forwarding function that calls <code>cbf_H5Arequire_cmp2_ULP</code> with the appropriate arguments to compare two
     strings. The <code>strcmp</code> function is used for string comparison, with a small wrapper to verify array
     length:

     <code><pre>\/\*\* a possible implementation of a function to compare two strings for equality \*\/
static int cmp_string
	(const void * const a,
	const void * const b,
	const size_t N,
	const void * const params)
{
     \/\* first ensure the arrays have one element each \*\/
	if (1 != N) return 1;
     \/\* then forward to 'strcmp' for the actual comparison \*\/
	else return strcmp(a,b);
     }</pre></code>

     \param location HDF5 object to which the string attribute should/will belong.
     \param name The name of the attribute.
     \param value The value which the attribute should/will have.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	/* TODO: allow a buffer to be provided to avoid malloc/free */
	int cbf_H5Arequire_string
    (const hid_t location,
     const char * const name,
     const char * const value)
	{
		int error = CBF_SUCCESS;
		if (!value) error |= CBF_ARGUMENT;
		if (CBF_SUCCESS==error) {
		hid_t h5atype = CBF_H5FAIL;
		error |= cbf_H5Tcreate_string(&h5atype,strlen(value));
            error |= CBFM_H5Arequire_cmp2(location,name,0,0,h5atype,h5atype,value,0,cmp_string,0);
		cbf_H5Tfree(h5atype);
		}
		return error;
	}

	/**
     Attempt to close an attribute, but don't modify the identifier that described it.
     
     \param ID The HDF5 attribute to be closed.
     \sa cbf_H5Acreate
     \sa cbf_H5Afind
     \sa cbf_H5Aread
     \sa cbf_H5Aread_string
     \sa cbf_H5Awrite
     \sa cbf_H5Arequire_cmp2
     \sa cbf_H5Arequire_cmp2_ULP
     \sa cbf_H5Arequire_string
     \sa cbf_H5Afree
     \return An error code.
     */
	int cbf_H5Afree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Aclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}
    
	/*
	find/create/free hdf5 datasets without directly using hdf5 API.
	TODO: function to support arbitrary dataspace/dcpl, and forward to it.
	*/

	/**
     The <code>dataset</code> parameter gives a location to store the dataset for use by the caller, for example to
     add an attribute to it. If non-zero the returned handle MUST be free'd by the caller with <code>cbf_H5Dfree</code>.
     
     If the <code>name</code> is null, an anonymous dataset is created. 

     The dimensions of the dataset to create are given in <code>dim</code>. The maximum extents of the dataset are
     given in <code>max</code>, which uses the values in <code>dim</code> as defaults if set to a null pointer.
     Each element of <code>max</code> must be at least as large as the corresponding element of <code>dim</code>.
     The dataset created will be a fixed-size dataset unless one of the elements of <code>max</code> is set to
     <code>H5S_UNLIMITED</code>.

     A chunk size must be given in the <code>chunk</code> argument if any element of <code>max</code> is set to
     <code>H5S_UNLIMITED</code> or is greater than the corresponding element of <code>dim</code>. If the dataset
     should not be chunked then a null pointer should be given.

     The <code>dim</code>, <code>max</code> and <code>chunk</code> arrays - if given - must each contain <code>rank</code> elements.

     This function will fail if a link with the same name already exists in <code>location</code>.
     
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Dcreate
    (const hid_t location, /**< The hdf5 group/file in which to put the dataset. */
     hid_t * const dataset, /**< An optional pointer to a location where the dataset handle should be stored. */
     const char * const name, /**< The name of the new dataset. */
     const int rank, /**< The rank of the data. */
     const hsize_t * const dim, /**< The dimensions of the dataset to create. Unused if <code>rank == 0</code>. */
     const hsize_t * const max, /**< The maximum size of each dimension. Unused if <code>rank == 0</code>. */
     const hsize_t * const chunk, /**< The chunk size for the dataset. */
     const hid_t type /**< The type of each data element in the file. */)
	{
		/* define variables & check args */
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(location) || (rank && !dim) || rank<0 || H5I_DATATYPE!=H5Iget_type(type)) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t dataset_local = CBF_H5FAIL;
		    hid_t dataSpace = CBF_H5FAIL;
			hid_t dcpl = CBF_H5FAIL;
			hid_t * const dsetp = dataset ? dataset : &dataset_local;
			htri_t exists = name?H5Lexists(location,name,H5P_DEFAULT):0;
			CBF_H5CALL(dcpl = H5Pcreate(H5P_DATASET_CREATE));
			CBF_CALL(cbf_H5Screate(&dataSpace, rank, dim, max));
			/* check if some more variables are valid */
			if (rank && max) {
			const hsize_t * m;
			for (m = max; m != max+rank; ++m) {
				if (H5S_UNLIMITED == *m) {
						if (!chunk) error |= CBF_ARGUMENT;
				}
			}
		}
		/* allow dataset to be chunked */
			if (rank && chunk) CBF_H5CALL(H5Pset_chunk(dcpl,rank,chunk));
			if (exists < 0) {
                cbf_debug_print("error: couldn't check is dataset exists");
                error |= CBF_H5ERROR;
			} else if (exists) {
				cbf_debug_print("error: dataset already exists");
				error |= CBF_H5ERROR;
			} else {
                if (name) {
				    CBF_H5CALL(*dsetp = H5Dcreate2(location,name,type,dataSpace,H5P_DEFAULT,dcpl,H5P_DEFAULT));
                } else {
                    CBF_H5CALL(*dsetp = H5Dcreate_anon(location,type,dataSpace,dcpl,H5P_DEFAULT));
                }
			}
		if (cbf_H5Ivalid(dataSpace)) H5Sclose(dataSpace);
		if (cbf_H5Ivalid(dcpl)) H5Pclose(dcpl);
			/* if the dataset object is requested then return it, otherwise close it */
			cbf_H5Dfree(dataset_local);
		}
		return error;
	}
    
    
    
	/* \brief Look for a dataset with the given properties.
     
     Succeeds without returning a valid dataset ID if no dataset exists and fails if one with different properties exists.
     Finding that the dataset doesn't exist is not a failure - the function worked and returned useful information.
     So, if it returns \c CBF_SUCCESS then the dataset must be free'd at some point, otherwise it doesn't need to be free'd.
     
     Use as:
     \code
     int error = cbf_H5Dfind(., &dataset, ...);
     if (CBF_SUCCESS==error) {
     if (cbf_H5Ivalid(dataset)) {
     use_existing_dataset(dataset);
     } else {
     cbf_H5Dcreate(...);
     use_new_datset(dataset);
     }
     } else {
     handle_error(error);
     }
     \endcode
     
     \param location The hdf5 group/file in which to put the dataset.
     \param dataset A pointer to a HDF5 object identifier that is set to the location of a valid object or an invalid value if the function
     succeeds, otherwise is left in an undefined state.
     \param name The name of the existing/new dataset.
     \param rank See \c cbf_H5Dcreate
     \param dim See \c cbf_H5Dcreate
     \param max See \c cbf_H5Dcreate
     \param chunk See \c cbf_H5Dcreate
     \param type See \c cbf_H5Dcreate
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code indicating whether the function successfully determined the presence (or otherwise) of an appropriate dataset.
     */
	int cbf_H5Dfind
    (const hid_t location,
     hid_t * const dataset,
     const char * const name,
     const int rank,
     const hsize_t * const dim,
     const hsize_t * const max,
     const hsize_t * const chunk,
     const hid_t type)
	{
		/* check the arguments */
		if (!cbf_H5Ivalid(location) || !dataset || !name || (!!rank && !dim) || rank<0) return CBF_ARGUMENT;
        
		/* check if the link exists */
		const htri_t l = H5Lexists(location, name, H5P_DEFAULT);
		if (l < 0) return CBF_H5ERROR;
		else if (!l) {
			*dataset = CBF_H5FAIL;
			return CBF_SUCCESS;
		} else {
			/* check if the group exists */
			const htri_t e = H5Oexists_by_name(location, name, H5P_DEFAULT);
			if (e < 0) return CBF_H5ERROR;
			else if (!e) {
				/* The link exists but the object doesn't - try to remove the link & tell the caller that there is no dataset */
				if (H5Ldelete(location, name, H5P_DEFAULT) < 0) return CBF_H5ERROR;
				else {
					*dataset = CBF_H5FAIL;
					return CBF_SUCCESS;
				}
			} else {
				/* my object exists - check its type */
				hid_t g = H5Oopen(location, name, H5P_DEFAULT);
				if (H5I_DATASET == H5Iget_type(g)) {
					int error = CBF_SUCCESS;
					/* it's a dataset - check its properties */
					hid_t currSpace = H5Dget_space(g);
					hid_t currType = H5Dget_type(g);
					hid_t dataSpace = CBF_H5FAIL;
					cbf_reportFail(cbf_H5Screate(&dataSpace, rank, dim, max), error);
					if (CBF_SUCCESS==error) {
						/* Check space */
						const htri_t eq = H5Sextent_equal(currSpace,dataSpace);
						if (eq < 0) error |= CBF_H5ERROR;
						else if (!eq) error |= CBF_H5DIFFERENT;
						else /* success */;
					}
					/* TODO: Check chunk? */
					if (CBF_SUCCESS==error) {
				 		/* check the datatype is correct */
						const htri_t eq = H5Tequal(currType,type);
						if (eq<0) error |= CBF_H5ERROR;
						else if (!eq) error |= CBF_H5DIFFERENT;
						else /* success */;
					}
					if (cbf_H5Ivalid(currType))H5Tclose(currType);
					if (cbf_H5Ivalid(currSpace))H5Sclose(currSpace);
					if (cbf_H5Ivalid(dataSpace))H5Sclose(dataSpace);
					*dataset = CBF_SUCCESS==error ? g : CBF_H5FAIL;
					return error;
				} else {
					/* not a dataset - close the object & fail */
					H5Oclose(g);
					return CBF_H5DIFFERENT;
				}
			}
		}
	}


	/**
     Returns <code>CBF_NOTFOUND</code> without modifying <code>dataset</code> if no dataset exists and fails without
	modifying <code>dataset</code> if one with different properties exists. A dataset will be 'found' if it has the
     same name and a maximum size which is at least as big as the size requested in <code>max</code>.

     A buffer of <code>rank</code> elements pointed to by <code>buf</code> may be used to store the array of
	maximum extents for a potentially matching dataset, in order to avoid the use of <code>malloc</code> &
     <code>free</code> for very small amounts of memory.

     Use as:
     
     <code><pre>\/\* Get the return code from the function call, \*\/
const int found = cbf_H5Dfind(location, &dataset, ...);
     \/\* and check what it was: \*\/
if (CBF_SUCCESS==found) {
     \/\* A dataset already existed and I have a handle for it: \*\/
     use_existing_dataset(dataset);
} else if (CBF_NOTFOUND==found) {
     \/\* No matching dataset existed, so I can create one: \*\/
	cbf_H5Dcreate(location, &dataset, ...);
     use_new_datset(dataset);
     } else {
     \/\*
	The function call failed, do something with the error.
	In this case, store it for later use and print a message.
     \*\/
	error |= found;
     cbf_debug_print(cbf_strerror(error));
     }
     \/\* clean up: \*\/
     cbf_H5Dfree(dataset);</pre></code>

     \param location The hdf5 group/file in which to put the dataset.
     \param dataset A pointer to a HDF5 object identifier that is set to the location of
     a valid object if the function succeeds, otherwise is left in an undefined state.
     \param name The name of the existing/new dataset.
	\param rank The rank of the data, must be equal to the length of the <code>max</code> and <code>buf</code> arrays, if they are given.
	\param max The (optional) maximum size of each dimension, pointer or an array of length <code>rank</code> where
		<code>0 &lt;= max[i] &lt;= H5S_UNLIMITED</code> for <code>i = [0, rank)</code>, unused if <code>rank == 0</code>.
	\param buf An optional buffer with <code>rank</code> elements which may be used to store the
		current maximum dimensions of a potential match to avoid a malloc/free call.
     \param type The type of each data element in the file. If an invalid type is given a dataset of any type may be returned.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return <code>CBF_SUCCESS</code> if a matching dataset was found, <code>CBF_NOTFOUND</code> if nothing with the same
     name was found, some other error code otherwise.
     */
	int cbf_H5Dfind2
    (const hid_t location,
     hid_t * const dataset,
     const char * const name,
     const int rank,
     const hsize_t * const max,
     hsize_t * const buf,
     const hid_t type)
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(location) || !dataset || !name || rank<0) {
			error |= CBF_ARGUMENT;
		} else {
            /* check if the link exists */
			const htri_t l = H5Lexists(location, name, H5P_DEFAULT);
            if (l < 0) {
				cbf_debug_print2("error: Could not check if link '%s' exists\n",name);
				error |= CBF_H5ERROR;
            } else if (!l) {
				error |= CBF_NOTFOUND;
            } else {
                /* check if the linked object exists */
                const htri_t e = H5Oexists_by_name(location, name, H5P_DEFAULT);
                if (e < 0) {
                    cbf_debug_print2("Could not check if object '%s' exists\n",name);
                    error |= CBF_H5ERROR;
                } else if (!e) {
                    /* The link exists but the object doesn't - try to remove the link & tell the caller that there is no dataset */
                    if (H5Ldelete(location, name, H5P_DEFAULT) < 0) {
                        cbf_debug_print2("Could not remove dead link '%s'\n",name);
                        error |= CBF_H5ERROR;
                    } else {
                        error |= CBF_NOTFOUND;
                    }
                } else {
                    /* my object exists - check its type */
                    hid_t g = H5Oopen(location, name, H5P_DEFAULT);
					if (!cbf_H5Ivalid(g)) {
						error |= CBF_H5ERROR;
					} else {
						if (H5I_DATASET != H5Iget_type(g)) {
							error |= CBF_H5DIFFERENT;
						} else {
                            /* it's a dataset - check its properties */
                            const hid_t currSpace = H5Dget_space(g);
 							if (!cbf_H5Ivalid(currSpace)) {
								cbf_debug_print("error: couldn't get data space");
								error |= CBF_H5ERROR;
							} else {
                                const int currRank = H5Sget_simple_extent_dims(currSpace, 0, 0);
                                if (currRank < 0) {
                                    cbf_debug_print2("Could not get rank of '%s'\n",name);
                                    error |= CBF_H5ERROR;
                                } else if (currRank != rank) {
                                    cbf_debug_print3("error: Current rank of '%d' differs from expected rank of '%d'\n",currRank, rank);
                                    error |= CBF_H5DIFFERENT;
                                } else if (CBF_SUCCESS==error && max && rank>0) {
                                    /* Check dataspace if it makes sense to do so */
                                    hsize_t * const _buf = buf ? 0 : malloc(rank*sizeof(hsize_t));
                                    hsize_t * const currMax = buf ? buf : _buf;
                                    if (H5Sget_simple_extent_dims(currSpace, 0, currMax)<0) {
                                        cbf_debug_print2("Could not get extent of '%s'\n",name);
                                        error |= CBF_H5ERROR;
                                    }
                                    int i = 0;
                                    for (; i != currRank; ++i) {
                                        if (currMax[i] != max[i] && currMax[i] < max[i]) {
                                            error |= CBF_H5DIFFERENT;
                                        }
                                    }
                                    free((void*)_buf);
                                }
                            }
                            cbf_H5Sfree(currSpace);
                            if (CBF_SUCCESS==error && H5I_DATATYPE==H5Iget_type(type)) {
                                /* check the datatype is correct */
                                const hid_t currType = H5Dget_type(g);
                                if (!cbf_H5Ivalid(currType)) {
                                    cbf_debug_print("error: couldn't get data space");
                                    error |= CBF_H5ERROR;
                                } else {
                                    const htri_t eq = H5Tequal(currType,type);
                                    if (eq<0) {
                                        cbf_debug_print2("error: couldn't test type of '%s'\n",name);
                                        error |= CBF_H5ERROR;
                                    } else if (!eq) error |= CBF_H5DIFFERENT;
                                }
                                cbf_H5Tfree(currType);
                            }
                            /* return the dataset & transfer ownership of it to the caller, or keep it to free it later */
                            if (CBF_SUCCESS==error) {
                                *dataset = g;
                                g = CBF_H5FAIL;
                            } else {
                                *dataset = CBF_H5FAIL;
                            }
                        }
                    }
                    if (cbf_H5Ivalid(g)) H5Oclose(g);
                }
            }
        }
        return error;
    }

	/**
     Ensure a dataset of the given <code>rank</code> exists and can hold at least as many elements as specified in
	<code>max</code>. If no dataset exists then one will be created with dimensions of [0, 0, ... 0].
     <code>cbf_H5Dfind</code> and <code>cbf_H5Dcreate</code> are used in the implementation of this function.

     An existing dataset may be found using <code>cbf_H5Dfind2(location, dataset, name, rank, max, buf, type)</code>.
     If no dataset can be found then a dataset will be created by setting each element of a buffer of length
     <code>rank</code> to zero and using <code>cbf_H5Dcreate(location, dataset, name, rank, buffer, max, chunk, type)</code>.
     A buffer of <code>rank</code> elements may be provided to avoid using malloc to allocate memory for a small array
     whose size may already be known.

     The value pointed to by <code>dataset</code> should be a valid object identifier if the function exits successfully,
     and will be left in an undefined state otherwise.
     
     This is roughly equivalent to:
     
     <code><pre>const int error = cbf_H5Dfind2(location, dataset, name, rank, max, buf, type);
     if (CBF_NOTFOUND==error) {
     int i;
     for (i = 0; i != rank; ++i) buf[i] = 0;
     return cbf_H5Dcreate(location, dataset, name, rank, buf, max, chunk, type);
     } else {
     \/\* 'error' may be 'CBF_SUCCESS' or could indicate an error: \*\/
     return error;
     }</pre></code>
     
     but contains more sophisticated error handling code and allows for some parameters to be omitted.
     
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
	\return An error code.
	*/
	int cbf_H5Drequire
    (const hid_t location, /**< The hdf5 group/file in which to put the dataset. */
     hid_t * const dataset, /**< A pointer to a location to store the dataset. */
     const char * const name, /**< The name of the existing/new dataset. */
     const int rank, /**< The rank of the data. */
     const hsize_t * const max, /**< The (optional) maximum size of each dimension. */
     const hsize_t * const chunk, /**< The chunk size used if creating a new dataset. */
     hsize_t * const buf, /**< An optional buffer with <code>rank</code> elements. */
     const hid_t type /**< The type of each data element in the file. */)
	{
		int error = CBF_SUCCESS;
		if (rank < 0) {
			error |= CBF_ARGUMENT;
		} else {
		int found = CBF_SUCCESS;
			hid_t dset = CBF_H5FAIL; /* always free'able */
			hid_t * dsetp = dataset ? dataset : &dset; /* always usable */
		found = cbf_H5Dfind2(location,dsetp,name,rank,max,buf,type);
		if (CBF_SUCCESS == found) {
			/* cbf_H5Dfind already checked the dimensions & type, so I don't need to do anything here */
		} else if (CBF_NOTFOUND==found) {
			/* create a suitable dataset */
				hsize_t * const _buf = (buf || !rank) ? NULL : malloc(rank*sizeof(hsize_t)); /* always free'able */
				hsize_t * const dim = buf ? buf : _buf; /* always usable */
			hsize_t * it;
			for (it = dim; it != dim+rank; ++it) *it = 0;
				CBF_CALL(cbf_H5Dcreate(location,dsetp,name,rank,dim,max,chunk,type));
			free((void*)_buf);
		} else {
			error |= found;
			/* maybe report the failure? */
                cbf_debug_print(cbf_strerror(error));
		}
		cbf_H5Dfree(dset);
		}
		return error;
	}

	/**
     Insert a slice of data into <code>dataset</code> with the appropriate <code>offset</code> &
     <code>stride</code>, ensuring that no existing data is lost due to resizing the dataset but not checking
     that previous data isn't being overwritten.

     The <code>offset</code>, <code>stride</code>, <code>count</code> and <code>buf</code> arrays must each
     have <code>rank</code> elements. If <code>stride</code> is set to the null pointer then a default of
     <code>[1, 1, 1, ..., 1]</code> will be used. An optional buffer may be provided in <code>buf</code> to
     avoid using malloc to allocate a small amount of memory whose size may actually be known at compile time.

     The <code>value</code> array should contain <code>count[0] * count[1] * ... * count[rank-1] === product(count)</code> elements of data.
     
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
	\return An error code.
	*/
	int cbf_H5Dinsert
    (const hid_t dataset, /**< The dataset to write the data to. */
     const hsize_t * const offset, /**< Where to start writing the data. */
     const hsize_t * const stride, /**< The number of elements in the dataset to step for each element to be written. */
     const hsize_t * const count, /**< The number of elements in each dimension to be written. */
     hsize_t * const buf, /**< An optional buffer to avoid using the heap for small amounts of memory. */
     const void * const value, /**< The address of the data to be written. */
     const hid_t type) /**< The type of data in memory. */
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(dataset) || !offset || !count || !value || H5I_DATATYPE!=H5Iget_type(type)) {
			error |= CBF_ARGUMENT;
		} else {
			/* get the rank and current dimensions of the dataset */
			const hid_t oldSpace = H5Dget_space(dataset);
			const int rank = H5Sget_simple_extent_dims(oldSpace,0,0);
			hsize_t * const _buf = buf ? 0 : malloc(rank*sizeof(hsize_t));
			hsize_t * dim = buf ? buf : _buf;
			if (H5Sget_simple_extent_dims(oldSpace,dim,0) != rank) error |= CBF_H5ERROR;
			if (rank >= 0) {
				hid_t memSpace = !rank ? H5Screate(H5S_SCALAR) : H5Screate_simple(rank,count,0);
				hid_t newSpace = CBF_H5FAIL;
				/* extend the dimensions, if required */
				unsigned int i;
				for (i = 0; i != rank; ++i) {
					const hsize_t sz = offset[i] + (stride?stride[i]:1)*(count[i]-1)+1;
					dim[i] = (dim[i]>sz) ? dim[i] : sz;
				}
				CBF_H5CALL(H5Dset_extent(dataset,dim));
				newSpace = H5Dget_space(dataset);
				/* select elements & write the dataset */
				if (rank) {
					CBF_H5CALL(H5Sselect_hyperslab(newSpace, H5S_SELECT_SET, offset, stride, count, 0));
				} else {
					CBF_H5CALL(H5Sselect_all(newSpace));
				}
				CBF_H5CALL(H5Dwrite(dataset,type,memSpace,newSpace,H5P_DEFAULT,value));
				/* check local variables are properly closed */
				if (cbf_H5Ivalid(memSpace)) H5Sclose(memSpace);
				if (cbf_H5Ivalid(newSpace)) H5Sclose(newSpace);
			}
			if (cbf_H5Ivalid(oldSpace)) H5Sclose(oldSpace);
			free((void*)_buf);
		}
		return error;
	}

	/**
     Forwards to a HDF5 function to change the extent of <code>dataset</code>. The <code>dim</code> array must have
     the same number of elements as the rank of the dataset, but this can't be checked within this function.

     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Dset_extent
    (const hid_t dataset, /**< A handle for the dataset whose extent is to be changed. */
     const hsize_t * const dim /**< The new extent of the dataset, if the function succeeds. */)
	{
		int error = CBF_SUCCESS;
		if (!dim || !cbf_H5Ivalid(dataset) || H5I_DATASET!=H5Iget_type(dataset)) {
			error |= CBF_ARGUMENT;
		} else {
			CBF_H5CALL(H5Dset_extent(dataset,dim));
	}
		return error;
	}

    
	/* \brief Add some data to the specified position in the dataset, without checking what (if anything) was there before.
     
     Assumes the dataset has the appropriate size to contain all the data and overwrites any existing data that may be there.
     The \c rank of the dataset is assumed to be known, and the size of the array parameters is not tested.
     
     \param dataset The dataset to write the data to.
     \param offset Where to start writing the data, as an array of \c rank numbers.
     \param stride The number of elements in the dataset to step for each element to be written, where
     null is equivalent to a stride of [1, 1, 1, ..., 1], as an array of \c rank numbers.
     \param count The number of elements in each dimension to be written, as an array of \c rank numbers.
     \param value The address of the data to be written.
     
     \sa cbf_H5Dcreate
     \sa  cbf_H5Dfind2   
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dread
     \sa cbf_H5Drequire_scalar_F64LE
     \sa cbf_H5Drequire_string
     \sa cbf_H5Dfree
     \sa cbf_H5Ddestroy
     
     \return An error code.
     */
	int cbf_H5Dwrite
    (const hid_t dataset,
     const hsize_t * const offset,
     const hsize_t * const stride,
     const hsize_t * const count,
     const void * const value)
	{
		/* define variables & check args */
		int error = (!cbf_H5Ivalid(dataset)) ? CBF_ARGUMENT : CBF_SUCCESS;
		hid_t datatype = H5Dget_type(dataset);
		hid_t filespace = H5Dget_space(dataset);
		const int rank = H5Sget_simple_extent_ndims(filespace);
		hid_t memspace = !rank ? H5Screate(H5S_SCALAR) : H5Screate_simple(rank,count,0);
        hid_t memtype = H5Tget_native_type(datatype, H5T_DIR_ASCEND);
		if ((!!rank && (!offset || !count)) || rank<0) error |= CBF_ARGUMENT;
        
		/* check variables are valid */
		reportFail(cbf_H5Ivalid(filespace), CBF_H5ERROR, error);
		reportFail(cbf_H5Ivalid(datatype), CBF_H5ERROR, error);
        
		/* select elements & write the dataset */
		if (rank) {
			reportFail(H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, stride, count, 0)>=0, CBF_H5ERROR, error);
		} else {
			reportFail(H5Sselect_all(filespace)>=0, CBF_H5ERROR, error);
		}
		reportFail(H5Dwrite(dataset,memtype,memspace,filespace,H5P_DEFAULT,value)>=0, CBF_H5ERROR, error);
        
		/* check local variables are properly closed */
		if (cbf_H5Ivalid(memtype)) H5Tclose(memtype);
		if (cbf_H5Ivalid(memspace)) H5Sclose(memspace);
		if (cbf_H5Ivalid(filespace)) H5Sclose(filespace);
		if (cbf_H5Ivalid(datatype)) H5Tclose(datatype);
        
		/* done */
		return error;
	}

	
    /**
     Assumes the dataset has the appropriate size to contain all the data and overwrites any existing data that may
	be there. The <code>rank</code> of the dataset is assumed to be known, and the size of the array parameters is not
	tested. When <code>rank</code> is zero - in the case of scalar datasets - the <code>offset</code>,
	<code>stride</code> and <code>count</code> parameters are meaningless and should be omitted by setting them to
     zero.

     \param dataset The dataset to write the data to.
	\param offset Where to start writing the data, as an array of <code>rank</code> numbers.
     \param stride The number of elements in the dataset to step for each element to be written, where
	null is equivalent to a stride of [1, 1, 1, ..., 1], as an array of <code>rank</code> numbers.
	\param count The number of elements in each dimension to be written, as an array of <code>rank</code> numbers.
     \param value The address of the data to be written.
	\param type The type of data in memory.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Dwrite2
    (const hid_t dataset,
     const hsize_t * const offset,
     const hsize_t * const stride,
     const hsize_t * const count,
     const void * const value,
	 const hid_t type)
	{
		int error = CBF_SUCCESS;
		if (H5I_DATASET!=H5Iget_type(dataset) || !cbf_H5Ivalid(dataset) || !value || H5I_DATATYPE!=H5Iget_type(type)) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t filespace = H5Dget_space(dataset);
			if (!cbf_H5Ivalid(filespace)) {
				error |= CBF_H5ERROR;
				cbf_debug_print(cbf_strerror(error));
            } else {
			/* get some data from the dataspace */
		const int rank = H5Sget_simple_extent_ndims(filespace);
                if ((rank && (!offset || !count)) || rank<0) {
                    error |= CBF_ARGUMENT;
                } else {
                    hid_t memspace = rank ? H5Screate_simple(rank,count,0) : H5Screate(H5S_SCALAR);
				if (!cbf_H5Ivalid(memspace)) {
					error |= CBF_H5ERROR;
                        cbf_debug_print("couldn't create dataspace");
                    } else {
				/* select elements */
                        if (rank) {
                            CBF_H5CALL(H5Sselect_hyperslab(filespace,H5S_SELECT_SET,offset,stride,count,0));
                        } else {
                            CBF_H5CALL(H5Sselect_all(filespace));
			}
			/* write the dataset */
                        CBF_H5CALL(H5Dwrite(dataset,type,memspace,filespace,H5P_DEFAULT,value));
		}
                    cbf_H5Sfree(memspace);
                }
            }
            cbf_H5Sfree(filespace);
        }
		return error;
	}

        
        
    /* \brief Extract some existing data from a dataset at a known position.
         
         Read some data from a given location in the dataset to an existing location in memory.
         Does not check the length of the array parameters, which should all have \c rank elements or (in some cases) be null.
         
         \param dataset The dataset to read the data from.
         \param offset Where to start reading the data, as an array of \c rank numbers.
         \param stride The number of elements in the dataset to step for each element to be read, where
         null is equivalent to a stride of [1, 1, 1, ..., 1], as an array of \c rank numbers.
         \param count The number of elements in each dimension to be read, as an array of \c rank numbers.
         \param value The location where the data is to be stored.
         
         \sa cbf_H5Dcreate
         \sa  cbf_H5Dfind2   
         \sa cbf_H5Dset_extent
         \sa cbf_H5Dwrite
         \sa cbf_H5Drequire_scalar_F64LE
         \sa cbf_H5Drequire_string
         \sa cbf_H5Dfree
         \sa cbf_H5Ddestroy
         
         \return An error code.
         */
        int cbf_H5Dread
        (const hid_t dataset,
         const hsize_t * const offset,
         const hsize_t * const stride,
         const hsize_t * const count,
         void * const value)
        {
            /* define variables & check args */
            int error = (!cbf_H5Ivalid(dataset)) ? CBF_ARGUMENT : CBF_SUCCESS;
            hid_t datatype = H5Dget_type(dataset);
            hid_t filespace = H5Dget_space(dataset);
            const int rank = H5Sget_simple_extent_ndims(filespace);
            hid_t memspace = !rank ? H5Screate(H5S_SCALAR) : H5Screate_simple(rank,count,0);
            if ((!!rank && (!offset || !count)) || rank<0) error |= CBF_ARGUMENT;
            
            /* check variables are valid */
            reportFail(cbf_H5Ivalid(filespace), CBF_H5ERROR, error);
            reportFail(cbf_H5Ivalid(datatype), CBF_H5ERROR, error);
            
            /* select elements & read the dataset */
            if (!!rank) {
                reportFail(H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, stride, count, 0)>=0, CBF_H5ERROR, error);
            } else {
                reportFail(H5Sselect_all(filespace)>=0, CBF_H5ERROR, error);
            }
            reportFail(H5Dread(dataset, datatype, memspace, filespace, H5P_DEFAULT, value)>=0, CBF_H5ERROR, error);
            
            /* check local variables are properly closed */
            if (cbf_H5Ivalid(memspace)) H5Sclose(memspace);
            if (cbf_H5Ivalid(filespace)) H5Sclose(filespace);
            if (cbf_H5Ivalid(datatype)) H5Tclose(datatype);
            
            /* done */
            return error;
        }
        
    /**
     Read some data from a given location in the dataset to an existing location in memory. Does not check the
	length of the array parameters, which should all have <code>rank</code> elements or (in some cases) be
	<code>null</code>. When <code>rank</code> is zero - in the case of scalar datasets - the <code>offset</code>,
	<code>stride</code> and <code>count</code> parameters are meaningless and should be omitted by setting them to
     zero.

     \param dataset The dataset to read the data from.
	\param offset Where to start writing the data, as an array of <code>rank</code> numbers.
	\param stride The number of elements in the dataset to step for each element to be written, where
	null is equivalent to a stride of [1, 1, 1, ..., 1], as an array of <code>rank</code> numbers.
	\param count The number of elements in each dimension to be written, as an array of <code>rank</code> numbers.
     \param value The location where the data is to be stored.
	\param type The type of data in memory.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Dread2
    (const hid_t dataset,
     const hsize_t * const offset,
     const hsize_t * const stride,
     const hsize_t * const count,
	 void * const value,
	 const hid_t type)
	{
		/* define variables & check args */
        int error = CBF_SUCCESS;
        if (!cbf_H5Ivalid(dataset)) {
            error |= CBF_ARGUMENT;
        } else {
		hid_t filespace = H5Dget_space(dataset);
            if (!cbf_H5Ivalid(filespace)) {
                error |= CBF_H5ERROR;
            } else {
                /* get rank of dataset and dataspace of memory block */
		const int rank = H5Sget_simple_extent_ndims(filespace);
		hid_t memspace = !rank ? H5Screate(H5S_SCALAR) : H5Screate_simple(rank,count,0);
                if ((rank && (!offset || !count)) || rank<0) {
                    error |= CBF_ARGUMENT;
                } else if (!cbf_H5Ivalid(memspace)) {
                    error |= CBF_H5ERROR;
                } else {
		/* select elements & read the dataset */
		if (rank) {
                        CBF_H5CALL(H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, stride, count, 0));
		} else {
                        CBF_H5CALL(H5Sselect_all(filespace));
		}
                    CBF_H5CALL(H5Dread(dataset, type, memspace, filespace, H5P_DEFAULT, value));
                }
                cbf_H5Sfree(memspace);
            }
            cbf_H5Sfree(filespace);
        }
		return error;
	}

        
    /* \brief Write a scalar 64-bit floating point number as a dataset.
         
         Convenience function using the HDF5 abstraction layer to avoid the need to consider array-related
         parameters for a scalar dataset and to automatically set the string type to the correct size.
         
         \param location The group containing the new dataset.
         \param dataset An optional pointer to a place to store the new dataset.
         \param name The name of the new dataset.
         \param value The value of the new dataset.
         \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
         
         \sa cbf_H5Dcreate
         \sa cbf_H5Dfind
         \sa cbf_H5Dset_extent
         \sa cbf_H5Dwrite
         \sa cbf_H5Dread
         \sa cbf_H5Drequire_string
         \sa cbf_H5Dfree
         \sa cbf_H5Ddestroy
         
         \return An error code.
         */
        int cbf_H5Drequire_scalar_F64LE
        (const hid_t location,
         hid_t * const dataset,
         const char * const name,
         const double value)
        {
            int error = CBF_SUCCESS;
            hid_t _dataset = CBF_H5FAIL;
            error |=  cbf_H5Dfind(location,&_dataset,name,0,0,0,0,H5T_IEEE_F64LE);
            if (CBF_SUCCESS==error) {
                if (!cbf_H5Ivalid(_dataset)) {
                    error |= cbf_H5Dcreate(location,&_dataset,name,0,0,0,0,H5T_IEEE_F64LE);
                    error |= cbf_H5Dwrite(_dataset,0,0,0,&value);
                } else {
                    double data = 0./0.;
                    error |= cbf_H5Dread(_dataset,0,0,0,&data);
                    if (fabs(value - data)> 1.e-38+1.e-13*(fabs(value)+fabs(data))) {
                    cbf_debug_print4("Error: data doesn't match (%g vs %g) for nexus field '%s'\n",data,value,name);
                        error |= CBF_H5DIFFERENT;
                    }
                }
                /* cleanup temporary dataset? */
                if (dataset) *dataset = _dataset;
                else cbf_H5Dfree(_dataset);
            } else {
            cbf_debug_print2("Attempt to determine existence of nexus field '%s' failed\n",name);
            }
            return error;
        }
        
     /**
     Convenience function using the HDF5 abstraction layer to avoid the need to consider array-related parameters
     for a scalar dataset.It ensures that a scalar 64-bit IEEE floating point dataset exists with the appropriate
     name and (for an existing dataset) the correct value as determined by the comparison function <code>cmp</code>.
     
     \param location The group containing the new dataset.
     \param dataset An optional pointer to a place to store the new dataset.
     \param name The name of the new dataset.
     \param value The value of the new dataset.
     \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
	\param cmp_params Some extra data required by the comparison function.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
    int cbf_H5Drequire_scalar_F64LE2
			(const hid_t location,
     hid_t * const dataset,
     const char * const name,
		const double value,
                                      int (*cmp)(const void *, const void *, size_t))
	{
		int error = CBF_SUCCESS;
		int found = CBF_SUCCESS;
		hid_t _dataset = CBF_H5FAIL;
		hid_t * dset = dataset ? dataset : &_dataset;
		found =  cbf_H5Dfind2(location,dset,name,0,0,0,H5T_IEEE_F64LE);
		if (CBF_SUCCESS==found) {
				double data = 0./0.;
			error |= cbf_H5Dread2(*dset,0,0,0,&data,H5T_NATIVE_DOUBLE);
			if (cmp(&value, &data, 1)) {
                cbf_debug_print4("data doesn't match (%g vs %g) for nexus field '%s'\n",data,value,name);
					error |= CBF_H5DIFFERENT;
				}
		} else if (CBF_NOTFOUND==found) {
			error |= cbf_H5Dcreate(location,dset,name,0,0,0,0,H5T_IEEE_F64LE);
			error |= cbf_H5Dwrite2(*dset,0,0,0,&value,H5T_NATIVE_DOUBLE);
		} else {
			error |= found;
            cbf_debug_print2("Attempt to determine existence of nexus field '%s' failed\n",name);
		}
		/* cleanup temporary dataset */
		cbf_H5Dfree(_dataset);
		return error;
	}

    /**
     Convenience function using the HDF5 abstraction layer to avoid the need to consider array-related parameters
     for a scalar dataset. It ensures that a scalar 64-bit IEEE floating point dataset exists with the appropriate
     name and (for an existing dataset) the correct value as determined by the user-supplied comparison function
     <code>cmp</code>.
         
     It is implemented using some of the other dataset functions:
         
     - cbf_H5Dfind2
     - cbf_H5Dcreate
     - cbf_H5Dread2
     - cbf_H5Dwrite2
     
         \param location The group containing the new dataset.
         \param dataset An optional pointer to a place to store the new dataset.
         \param name The name of the new dataset.
         \param value The value of the new dataset.
         \param cmp A comparison function to test if a previously set value is equal to the value I asked for.
     \param cmp_params Some extra data which may be required by the comparison function.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
         \return An error code.
         */
        int cbf_H5Drequire_scalar_F64LE2_ULP
        (const hid_t location,
         hid_t * const dataset,
         const char * const name,
         const double value,
         int (*cmp)(const void *, const void *, size_t, const void *),
         const void * const cmp_params)
        {
            int error = CBF_SUCCESS;
            int found = CBF_SUCCESS;
        hid_t _dataset = CBF_H5FAIL; /* always free'able */
        hid_t * dset = dataset ? dataset : &_dataset; /* always usable */
            found =  cbf_H5Dfind2(location,dset,name,0,0,0,H5T_IEEE_F64LE);
            if (CBF_SUCCESS==found) {
				double data = 0./0.;
            CBF_CALL(cbf_H5Dread2(*dset,0,0,0,&data,H5T_NATIVE_DOUBLE));
                if (cmp(&value, &data, 1, cmp_params)) {
                cbf_debug_print4("data doesn't match (%g vs %g) for nexus field '%s'\n",data,value,name);
					error |= CBF_H5DIFFERENT;
				}
            } else if (CBF_NOTFOUND==found) {
            CBF_CALL(cbf_H5Dcreate(location,dset,name,0,0,0,0,H5T_IEEE_F64LE));
            CBF_CALL(cbf_H5Dwrite2(*dset,0,0,0,&value,H5T_NATIVE_DOUBLE));
            } else {
                error |= found;
            cbf_debug_print2("Attempt to determine existence of nexus field '%s' failed\n",name);
            }
            /* cleanup temporary dataset */
            cbf_H5Dfree(_dataset);
            return error;
        }

        
    /**
     Convenience function using the HDF5 abstraction layer to avoid the need to consider array-related parameters
     for a scalar dataset and to automatically set the string type to the correct size.

     \param location The group containing the new dataset.
     \param dataset An optional pointer to a place to store the new dataset.
     \param name The name of the new dataset.
     \param value The value of the new dataset.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Drequire_flstring
    (const hid_t location,
     hid_t * const dataset,
     const char * const name,
     const char * const value)
	{
		int error = CBF_SUCCESS;
        if (!value) {
            error |= CBF_ARGUMENT;
        } else {
            hid_t dataType = CBF_H5FAIL;
            CBF_CALL(cbf_H5Tcreate_string(&dataType,strlen(value)));
            if (CBF_SUCCESS==error) {
		int found = CBF_SUCCESS;
		hid_t _dataset = CBF_H5FAIL;
		hid_t * dset = dataset ? dataset : &_dataset;
		found =  cbf_H5Dfind2(location,dset,name,0,0,0,dataType);
		if (CBF_SUCCESS==found) {
			hid_t currType = H5Dget_type(*dset);
                    if (!cbf_H5Ivalid(currType)) {
                        error |= CBF_H5ERROR;
                    } else {
			char * data = malloc(H5Tget_size(currType));
                        if (!data) {
                            error |= CBF_ALLOC;
                        } else if (CBF_SUCCESS!=(error|=cbf_H5Dread2(*dset,0,0,0,(void * const)(data),dataType))) {
                            cbf_debug_print(cbf_strerror(error));
                        } else if (strcmp(value, data)) {
					error |= CBF_H5DIFFERENT;
                            cbf_debug_print4("data doesn't match ('%s' vs '%s') for dataset '%s'\n",data,value,name);
				}
			/* 'data' is either allocated by me or by the HDF5 library: always free it */
				free((void*)data);
                    }
                    H5Tclose(currType);
		} else if (CBF_NOTFOUND==found) {
                    CBF_CALL(cbf_H5Dcreate(location,dset,name,0,0,0,0,dataType));
                    CBF_CALL(cbf_H5Dwrite2(*dset,0,0,0,(const void * const)(value),dataType));
		} else {
			error |= found;
                    cbf_debug_print2("Attempt to determine existence of nexus field '%s' failed\n",name);
		}
		cbf_H5Dfree(_dataset);
            }
            cbf_H5Tfree(dataType);
        }
		return error;
	}

    /**
     Attempt to close a dataset, but don't modify the identifier that described it.

     \param ID The HDF5 dataset to be closed.
     \sa cbf_H5Dcreate
     \sa cbf_H5Dfind2
     \sa cbf_H5Drequire
     \sa cbf_H5Dinsert
     \sa cbf_H5Dset_extent
     \sa cbf_H5Dwrite2
     \sa cbf_H5Dread2
     \sa cbf_H5Drequire_scalar_F64LE2
     \sa cbf_H5Drequire_scalar_F64LE2_ULP
     \sa cbf_H5Drequire_flstring
     \sa cbf_H5Dfree
     \return An error code.
     */
	int cbf_H5Dfree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Dclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}

	/* Custom HDF5 types - to get the correct string type for datasets in a consistent way */

	/** \brief Get a HDF5 string datatype with a specified length.

     Convenience function to create a string datatype suitable for use when storing a string of length
     <code>len</code>, returning it in the identifier pointed to by <code>type</code>.

     \param type A pointer to a the HDF5 handle of the new datatype, which should be free'd with \c cbf_H5Tfree
     \param len The length of the string datatype - should be \c strlen() or \c H5T_VARIABLE
     \sa cbf_H5Tcreate_string
     \sa cbf_H5Tfree
     \return An error code.
     */
    int cbf_H5Tcreate_string(hid_t * const type, const size_t len)
	{
        int error = CBF_SUCCESS;
        CBF_H5CALL(*type = H5Tcopy(H5T_C_S1));
        CBF_H5CALL(H5Tset_size(*type,H5T_VARIABLE==len?len:len+1));
        return error;
	}

	/** \brief Close a HDF5 datatype identifier

     Attempt to close a datatype identifier, but don't modify the identifier that described it.

     \param ID The HDF5 datatype to be closed.
     \sa cbf_H5Tcreate_string
     \sa cbf_H5Tfree
     \return An error code.
     */
	int cbf_H5Tfree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Tclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}

	/* HDF5 dataspace functions: I need a uniform method of creating data spaces to ensure correct operation of comparison functions */

	/** \brief Create a dataspace with some given values

     Helper function which creates a HDF5 dataspace.

     Maximum dimensions can be set to infinity by passing <code>H5S_UNLIMITED</code> in the appropriate slot of the
	<code>max</code> parameter. If <code>rank</code> is zero then neither <code>dim</code> nor <code>max</code> are
     used and a scalar dataspace is created. If <code>rank</code> is non-zero and <code>dim</code> is a null pointer
     then <code>ID</code> will not be modified and the function will fail. If <code>rank</code> is non-zero and
     <code>max</code> is a null pointer the maximum length is set to the current length as given by <code>dim</code>.

     \param ID A pointer to a HDF5 identifier that will contain the new dataspace.
     \param rank The number of dimensions of the new dataspace.
     \param dim The current size of each dimension of the dataspace, should be an array of length \c rank .
     \param max The maximum size of each dimension, should be an array of length \c rank .
     \sa cbf_H5Screate
     \sa cbf_H5Sfree
     \return An error code.
     */
	int cbf_H5Screate
    (hid_t * const ID,
     const int rank,
     const hsize_t * const dim,
     const hsize_t * const max)
	{
        int error = CBF_SUCCESS;
        if (!ID || (rank && !dim) || rank<0) {
            error |= CBF_ARGUMENT;
        } else {
            hid_t space = rank ? H5Screate_simple(rank, dim, max) : H5Screate(H5S_SCALAR);
            if (!cbf_H5Ivalid(space)) {
                error |= CBF_H5ERROR;
            } else {
				*ID = space;
		}
	}
        return error;
    }

	/** \brief Close a HDF5 dataspace identifier

     Attempt to close a dataspace identifier, but don't modify the identifier that described it.

     \param ID The HDF5 dataspace to be closed.
     \sa cbf_H5Screate
     \sa cbf_H5Sfree
     \return An error code.
     */
	int cbf_H5Sfree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Sclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}

    /* HDF5 objects */

    /**
     Compare two HDF5 object ID's for equality. This follows the standard practice of returning zero if objects
     should be considered equal, and the HDF5 practice of returning a negative number if there is an error.

     \param id0 An HDF5 identifier.
     \param id1 An HDF5 identifier.
     \sa cbf_H5Ocmp
     \sa cbf_H5Ivalid
     \return 0 if equal, a positive value if not equal, or a negative value if there is an error.
     */
    htri_t cbf_H5Ocmp
    (const hid_t id0,
     const hid_t id1)
    {
        htri_t error = 0;
        herr_t valid0 = H5Iis_valid(id0);
        herr_t valid1 = H5Iis_valid(id1);
        if (valid0 < 0 || valid1 < 0) {
            error = -1;
        } else if (!valid0 || !valid1) {
            error = 1;
        } else {
            H5O_info_t info0, info1;
            herr_t err0 = H5Oget_info(id0,&info0);
            herr_t err1 = H5Oget_info(id1,&info1);
            if (err0 < 0 || err1 < 0) {
                error = -1;
            } else if (info0.fileno != info1.fileno || info0.addr != info1.addr || info0.type != info1.type) {
                error = 1;
            } else {
                error = 0;
            }
        }
        return error;
    }

	/**
	Attempt to close an object identifier of unknown type, but don't modify the identifier that described it.
    
	\param ID The HDF5 object to be closed.
	\sa cbf_H5Ocmp
	\sa cbf_H5Ofree
	\sa cbf_H5Ivalid
	\return An error code.
	 */
	int cbf_H5Ofree(const hid_t ID)
	{
		if (cbf_H5Ivalid(ID)) return H5Oclose(ID)>=0 ? CBF_SUCCESS : CBF_H5ERROR;
		else return CBF_ARGUMENT;
	}


    /****************************************************************
     End of section of code extracted from J. Sloan's
     cbf_hdf5_common.c
     ****************************************************************/

    /****************************************************************
     The following section of code is extracted from J. Sloan's
     config.c
     ****************************************************************/


    /* Some error codes for use by the parsing functions - definitions should not be visible */
	const int cbf_configError_success = 0;
	const int cbf_configError_unexpectedInput = 1;
	const int cbf_configError_expectedDelimeter = 2;
	const int cbf_configError_expectedNumber = 3;
	const int cbf_configError_openingFile = 4;
	const int cbf_configError_expectedString = 5;
	const int cbf_configError_duplicateField = 6;
	const int cbf_configError_unexpectedEOF = 7;
	const int cbf_configError_undefinedValue = 8;
	const int cbf_configError_invalidDependency = 9;
	const int cbf_configError_missingDependency = 10;
	const int cbf_configError_loop = 11;

	static int cbf_isblank (int c)
	{
		return (' ' == c || '\t' == c);
	}
    
    /*
     Tokenise an input stream, returning one token at a time into the given buffer.

     \param buf A pointer to a realloc-able buffer for storing the input, free'd when EOF is reached.
     \param n The current size of \c buf.
     \param ln The current line number of the file.
     \param pre The previous character, needed to test for unexpected EOL state.
     \param stream The stream to be tokenised.

	\return A parser error code.
     */
	static int cbf_configParse_scan(char * * const buf, size_t * n, size_t * ln, char * const pre, FILE * stream)
    {
        int c = 0; /* current character */
        size_t k = 0; /* current line length */

        /* check that sensible arguments are given */
        assert(buf);
        assert(n);
        assert(ln);
        assert(pre);
        assert(stream);

        /* skip blanks & comments to get to an interesting character */
        do {
            c = fgetc(stream);
            if (feof(stream)) break;
            *pre = c;
            if ('\n' == c) ++*ln;
            if ('#' == c) {
                do {
                    c = fgetc(stream);
                    if (feof(stream)) break;
                    *pre = c;
                    if ('\n' == c) ++*ln;
				} while (!isspace(c) || cbf_isblank(c));
            }
			if (cbf_isblank(c)) continue;
            else break;
        } while (1);

        /* if I am at the end of the stream, free the buffer & return 0 */
        if (feof(stream)) {
            free((void*)(*buf));
            *buf = 0;
            *n = 0;
			return '\n'==*pre ? cbf_configError_success : cbf_configError_unexpectedEOF;
        }

        /* I have a token: read it */
        if (isspace(c)) {
            /* it's a newline token */
            cbf_push_buf('\n', buf, n, &k);
        } else {
            /* it's a string : leave the terminating character in the stream as it may be a token itself */
            if ('[' == c || ']' == c) {
                /* it's a vector start or end token : match the structure of a vector at a higher level */
                cbf_push_buf(c, buf, n, &k);
            } else while (1) {
                cbf_push_buf(c, buf, n, &k);
                c = fgetc(stream);
                if (feof(stream)) break;
                *pre = c;
                if (isspace(c) || '[' == c || ']' == c) {
                    ungetc(c, stream);
                    break;
                }
            }
        }
        /* null-terminate the token */
        cbf_push_buf('\0', buf, n, &k);

		return (feof(stream) && '\n'!=*pre) ? cbf_configError_unexpectedEOF : cbf_configError_success;
    }

    /**
     The returned string is "none" for success, "unknown error" if the given error code is
     not recognised and a non-empty string briefly describing the error otherwise.
     
     The returned string must not be free'd.
     
     \param error An error returned by a <code>cbf_config_*</code> function.
     
     \return A string describing the error.
     */
    const char * cbf_config_strerror(const int error)
    {
		if (error == cbf_configError_success) return "none";
		else if (error == cbf_configError_unexpectedInput) return "unexpected input";
		else if (error == cbf_configError_expectedDelimeter) return "expected a delimiter";
		else if (error == cbf_configError_expectedNumber) return "expected a number";
		else if (error == cbf_configError_openingFile) return "could not open file";
		else if (error == cbf_configError_expectedString) return "expected a string";
		else if (error == cbf_configError_duplicateField) return "duplicate data";
		else if (error == cbf_configError_undefinedValue) return "a value was not defined at point of use";
		else if (error == cbf_configError_invalidDependency) return "invalid dependency found";
		else if (error == cbf_configError_missingDependency) return "missing dependency";
		else if (error == cbf_configError_loop) return "dependency loop detected";
        else return "unknown error";
    }

	/* POD to define a basic set of configuration settings for an axis */
	typedef struct cbf_configItem_t
	{
		double vector[3];
		const char * minicbf;
		const char * nexus;
		const char * depends_on;
		struct cbf_configItem_t * next;
		int convert;
	} cbf_configItem_t;

    /*
	Initialises name & depends_on to null, vector to [0,0,0].
     */
	static cbf_configItem_t cbf_configItem_create()
    {
        cbf_configItem_t item;
        item.vector[0] = 0.;
        item.vector[1] = 0.;
        item.vector[2] = 0.;
		item.minicbf = NULL;
		item.nexus = NULL;
		item.depends_on = NULL;
		item.next = NULL;
		item.convert = 0;
        return item;
    }

	static void cbf_configItem_free(const cbf_configItem_t * item)
    {
		if (item) {
        free((void*)(item->minicbf));
        free((void*)(item->nexus));
        free((void*)(item->depends_on));
    }
    }

    /*
    Should not be manipulated directly, takes ownership of the config items which it contains.
    */
	struct cbf_config_t
    {
        size_t nItems;
        size_t maxItems;
        const char * sample_depends_on;
		cbf_configItem_t * item;
	};

    /**
     Allocates a new collection of configuration settings on the heap, and initialises it. The returned
     pointer should be destroyed by the caller.
     
     \return A newly allocated object for miniCBF configuration settings, or <code>NULL</code>.
     */
    cbf_config_t * cbf_config_create()
    {
		cbf_config_t * const vector = malloc(sizeof(cbf_config_t));
		if (vector) {
        vector->nItems = 0;
        vector->maxItems = 0;
        vector->sample_depends_on = NULL;
        vector->item = NULL;
		}
        return vector;
    }

    /**
	<p>Destroys an existing collection of configuration settings. The settings should have been obtained by a call to
	<code>cbf_config_create</code>.</p>
     
     \param vector The configuration data to be free'd.
     
     \return Nothing.
     */
	void cbf_config_free(const cbf_config_t * vector)
    {
		if (vector) {
        const cbf_configItem_t * it = vector->item;
		for (; it != vector->item+vector->nItems; ++it) cbf_configItem_free(it);
		free((void*)vector->item);
        free((void*)vector->sample_depends_on);
		free((void*)vector);
    }
    }

    /*
     Releases any previously held dependency and takes ownership of a new one.
     The given string will be free'd by the object when it is no longer needed.
     */
	static void cbf_config_setSampleDependsOn(cbf_config_t * vector, const char * const depends_on)
    {
		if (vector) {
        free((void*)(vector->sample_depends_on));
        vector->sample_depends_on = depends_on;
    }
    }

    /*
     \return The current dependency setting for the sample group, or null if not set.
     */
	static const char * cbf_config_getSampleDependsOn(const cbf_config_t * const vector)
    {
		if (vector) return vector->sample_depends_on;
		else return 0;
    }

    /*
	\return A pointer to an item in the vector that may be modified but should not be free'd,
	subsequent vector operations may invalidate this pointer.
	 */
	static cbf_configItem_t * cbf_config_begin(const cbf_config_t * const vector)
	{
		if (vector) return vector->item;
		else return 0;
	}

    /*
	\return A pointer to an item in the vector that may be modified but should not be free'd,
	subsequent vector operations may invalidate this pointer.
	 */
	static const cbf_configItem_t * cbf_config_end(const cbf_config_t * const vector)
	{
		if (vector) return vector->item+vector->nItems;
		else return 0;
	}

    /*
     \brief Append an item to the configuration vector.
     The vector will take ownership of the item's contents. This may invalidate any previously obtained pointers to items in the vector.
     \return An iterator to the new item, or NULL on failure.
     */
	static cbf_configItem_t * cbf_config_push(cbf_config_t * const vector, cbf_configItem_t item)
    {
		if (vector) {
        if (!(vector->nItems < vector->maxItems)) {
            /* increase the maximum number of items */
            const size_t k = 4;
            vector->maxItems = (size_t)(vector->nItems/k) * k + k;
            vector->item = realloc(vector->item, vector->maxItems*sizeof(cbf_configItem_t));
        }
        /* ensure I have enough items */
        assert(vector->maxItems > vector->nItems);

        /* add the item to the end of the vector & set the item count to the correct number. */
        vector->item[vector->nItems++] = item;
        return vector->item+vector->nItems-1;
		} else return 0;
    }

    /*
     \return An iterator to a matching entry, to the current end element if there is no matching entry, or NULL on failure.
     */
	static cbf_configItem_t * cbf_config_findMinicbf(const cbf_config_t * const vector, const char * const name)
    {
        cbf_configItem_t * it = cbf_config_begin(vector);
		const cbf_configItem_t * const end = cbf_config_end(vector);
		if (!vector || !name) return 0;
        while (end != it && (!it->minicbf || strcmp(it->minicbf,name))) ++it;
        return it;
    }

    /*
     \return An iterator to a matching entry, to the current end element if there is no matching entry, or NULL on failure.
     */
	static cbf_configItem_t * cbf_config_findNexus(const cbf_config_t * const vector, const char * const name)
    {
		cbf_configItem_t * it = cbf_config_begin(vector);
		const cbf_configItem_t * const end = cbf_config_end(vector);
		if (!vector || !name) return 0;
		while (end != it && (!it->nexus || strcmp(it->nexus,name))) ++it;
        return it;
    }

	/*
	<p>Looks for missing or cyclic dependencies:</p>
	<ul>
		<li>The base coordinate system is expected to be represented by ".", it is an error if any dependency within
		the chain leading to the sample object is not in the set and is not equal to this.</li>
		<li>Cyclic dependencies in the chain leading to the sample is also an error.</li>
		<li>Dependency chains not leading to the sample object are not tested.</li>
	</ul>
	<p>This also sets pointers in the config items to quickly locate their dependencies later on, and marks each axis
	in the chain to allow irrelevant axes to be skipped.</p>

	TODO: test to verify that loops can be caught.
	Need to factor out the loop body and count the number steps on a
	pre-defined loop to verify that it is identified on the correct step.

	\return <p>A parser error code.</p>
     */
	static int _cbf_config_validate(const cbf_config_t * const vector)
    {
		cbf_configItem_t * it1 = cbf_config_findNexus(vector,cbf_config_getSampleDependsOn(vector));
		cbf_configItem_t * it2 = it1;
		do {
			/* mark it2 for conversion & check dependency */
			it2->convert = 1;
			if (!it2->depends_on) return cbf_configError_missingDependency;
			if (!strcmp(it2->depends_on,".")) return cbf_configError_success;
			/* set & check it2->next */
			if (!it2->next) it2->next = cbf_config_findNexus(vector,it2->depends_on);
			if (cbf_config_end(vector)==it2->next) return cbf_configError_invalidDependency;
			/* increment it2 & check for loop */
			it2 = it2->next;
			if (it2==it1) return cbf_configError_loop;
			/* mark it2 for conversion & check dependency */
			it2->convert = 1;
			if (!it2->depends_on) return cbf_configError_missingDependency;
			if (!strcmp(it2->depends_on,".")) return cbf_configError_success;
			/* set & check it2->next */
			if (!it2->next) it2->next = cbf_config_findNexus(vector,it2->depends_on);
			if (cbf_config_end(vector)==it2->next) return cbf_configError_invalidDependency;
			/* increment it2 & check for loop */
			it2 = it2->next;
			if (it2==it1) return cbf_configError_loop;
			/* increment it1 */
			it1 = it1->next;
		} while (1);
		return cbf_configError_success;
    }

	static int cbf_configParse_extractVector
    (FILE * const configFile,
     FILE * const logFile,
     cbf_configItem_t * const it,
     char * * const buf,
     size_t * n,
     size_t * ln,
     char * const pre)
    {
        char * end = 0;

#define GET_TOKEN() \
CBFM_PROLOG { \
  const int e = cbf_configParse_scan(buf, n, ln, pre, configFile); \
    if (cbf_configError_success!=e) { \
	fprintf(logFile,"\nError: %s\n",cbf_config_strerror(e)); \
return e; \
} \
} CBFM_EPILOG

#define REQUIRE_TOKEN(TKN) \
CBFM_PROLOG { \
const char * const _tkn = (TKN); \
if (strcmp(_tkn,*buf)) { \
fprintf(logFile,"Config parsing error on line %lu: expected " #TKN ", got '%s'\n",*ln,*buf); \
    return cbf_configError_unexpectedInput; \
} \
} CBFM_EPILOG

#define REQUIRE_NOT_EOL() \
CBFM_PROLOG { \
if (!strcmp("\n",*buf)) { \
fprintf(logFile,"Config parsing error on line %lu: unexpected newline\n",*ln); \
    return cbf_configError_unexpectedInput; \
} \
} CBFM_EPILOG

        /* literal '['. */
        GET_TOKEN();
        REQUIRE_NOT_EOL();
        REQUIRE_TOKEN("[");
        GET_TOKEN();
        REQUIRE_NOT_EOL();
        errno = 0;
        it->vector[0] = strtod(*buf, &end);
        if (errno != 0 || end == *buf) {
            fprintf(logFile,"Config parsing error on line %lu: expected a number, got '%s'\n",*ln,*buf);
            return cbf_configError_expectedNumber;
        }
        GET_TOKEN();
        REQUIRE_NOT_EOL();
        errno = 0;
        it->vector[1] = strtod(*buf, &end);
        if (errno != 0 || end == *buf) {
            fprintf(logFile,"Config parsing error on line %lu: expected a number, got '%s'\n",*ln,*buf);
			return cbf_configError_expectedNumber;
        }
        GET_TOKEN();
        REQUIRE_NOT_EOL();
        errno = 0;
        it->vector[2] = strtod(*buf, &end);
        if (errno != 0 || end == *buf) {
            fprintf(logFile,"Config parsing error on line %lu: expected a number, got '%s'\n",*ln,*buf);
			return cbf_configError_expectedNumber;
        }
        /* literal ']'. */
        GET_TOKEN();
        REQUIRE_NOT_EOL();
        REQUIRE_TOKEN("]");

#undef GET_TOKEN
#undef REQUIRE_TOKEN
#undef REQUIRE_NOT_EOL

        return CBF_SUCCESS;
    }

	/**
     Parses a configuration file to extract a collection of configuration settings for a miniCBF file, storing them
	in the given configuration settings object. The pointer should have been obtained by a call to
	<code>cbf_config_create</code>. The configuration file format is described in the
     <code>minicbf2nexus</code> documentation.

     \param configFile The file from which the config settings should be read.
     \param logFile A stream to be used for logging error messages.
     \param vec An object describing the configuration settings.
     
     \return A parser error code.
	*/
    int cbf_config_parse
    (FILE * const configFile,
     FILE * const logFile,
     cbf_config_t * const vec)
    {
        char * tkn = 0;
        size_t n = 0, ln = 1;
        char pre = '\0';

#define GET_TOKEN() \
CBFM_PROLOG { \
	const int e = cbf_configParse_scan(&tkn, &n, &ln, &pre, configFile); \
	if (cbf_configError_success!=e) { \
		fprintf(logFile,"\nError: %s\n",cbf_config_strerror(e)); \
return e; \
} \
} CBFM_EPILOG

#define REQUIRE_TOKEN(TKN) \
CBFM_PROLOG { \
const char * const _tkn = (TKN); \
if (strcmp(_tkn,tkn)) { \
fprintf(logFile,"Config parsing error on line %lu: expected " #TKN ", got '%s'\n",ln,tkn); \
return cbf_configError_unexpectedInput; \
} \
} CBFM_EPILOG

#define REQUIRE_EOL() \
CBFM_PROLOG { \
if (strcmp("\n",tkn)) { \
fprintf(logFile,"Config parsing error on line %lu: expected '\\n', got '%s'\n",ln,tkn); \
return cbf_configError_unexpectedInput; \
} \
} CBFM_EPILOG

#define REQUIRE_NOT_EOL() \
CBFM_PROLOG { \
if (!strcmp("\n",tkn)) { \
fprintf(logFile,"Config parsing error on line %lu: unexpected newline\n",ln); \
return cbf_configError_unexpectedInput; \
} \
} CBFM_EPILOG

#define REQUIRE_NEXUS_AXIS() \
CBFM_PROLOG { \
if (strcmp(".",tkn) && cbf_config_end(vec) == cbf_config_findNexus(vec,tkn)) { \
fprintf(logFile,"Config parsing error on line %lu: Nexus axis '%s' not defined\n",ln,tkn); \
return cbf_configError_undefinedValue; \
} \
} CBFM_EPILOG

#define REQUIRE_VECTOR() \
CBFM_PROLOG { \
const int e = cbf_configParse_extractVector(configFile, logFile, it, &tkn, &n, &ln, &pre); \
if (cbf_configError_success!=e) { \
fprintf(logFile,"Error reading a vector: %s\n",cbf_config_strerror(e)); \
return e; \
} \
} CBFM_EPILOG

        /* first token of the line */
        GET_TOKEN();
        while (tkn) {
            if (!cbf_cistrcmp("map",tkn)) {
                /* storage that I don't need to free within this function */
                cbf_configItem_t * it;
                /* minicbf axis name */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                it = cbf_config_findMinicbf(vec,tkn);
                if (cbf_config_end(vec) != it) {
                    fprintf(logFile,"Config parsing error on line %lu: Duplicate axis definition for minicbf axis '%s'\n",ln,tkn);
                    return cbf_configError_duplicateField;
                }
                it = cbf_config_push(vec,cbf_configItem_create());
				it->minicbf = _cbf_strdup(tkn);
                /* literal 'to'. */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                REQUIRE_TOKEN("to");
                /* nexus axis name */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                if (cbf_config_end(vec) != cbf_config_findNexus(vec,tkn)) {
                    fprintf(logFile,"Config parsing error on line %lu: Duplicate axis definition for Nexus axis '%s'\n",ln,tkn);
                    return cbf_configError_duplicateField;
                }
				it->nexus = _cbf_strdup(tkn);
                /* newline */
                GET_TOKEN();
                REQUIRE_EOL();
            } else if (!cbf_cistrcmp("Sample",tkn)) {
                /* literal 'depends-on'. */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                REQUIRE_TOKEN("depends-on");
                /* nexus axis name */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                REQUIRE_NEXUS_AXIS();
				cbf_config_setSampleDependsOn(vec,_cbf_strdup(tkn));
                /* newline */
                GET_TOKEN();
                REQUIRE_EOL();
			} else if (!cbf_cistrcmp("\n",tkn)) {
            } else {
                /* find entry by nexus axis name */
                cbf_configItem_t * const it = cbf_config_findNexus(vec,tkn);
                if (cbf_config_end(vec) == it) {
                    fprintf(logFile,"Config parsing error on line %lu: Nexus axis '%s' not defined\n",ln,tkn);
                    return cbf_configError_undefinedValue;
                }
                /* match depends-on -> vector OR vector -> depends-on. */
                GET_TOKEN();
                REQUIRE_NOT_EOL();
                if (!cbf_cistrcmp("vector",tkn)) {
                    /* try to get a vector */
                    REQUIRE_VECTOR();
                    GET_TOKEN();
                    /* optional 'depends-on' */
                    if (!cbf_cistrcmp("depends-on",tkn)||!cbf_cistrcmp("depends_on",tkn)) {
                        /* nexus axis name */
                        GET_TOKEN();
                        REQUIRE_NOT_EOL();
                        REQUIRE_NEXUS_AXIS();
                        /* this is a potential memory leak */
						it->depends_on = _cbf_strdup(tkn);
                        GET_TOKEN();
                    }
                    /* check for newline */
                    REQUIRE_EOL();
                } else if (!cbf_cistrcmp("depends-on",tkn)||!cbf_cistrcmp("depends_on",tkn)) {
                    /* nexus axis name */
                    GET_TOKEN();
                    REQUIRE_NOT_EOL();
                    REQUIRE_NEXUS_AXIS();
                    /* this is a potential memory leak */
					it->depends_on = _cbf_strdup(tkn);
                    GET_TOKEN();
                    /* optional 'vector' */
                    if (!cbf_cistrcmp("vector",tkn)) {
                        /* try to get a vector */
                        REQUIRE_VECTOR();
                        GET_TOKEN();
                    }
                    /* check for newline */
                    REQUIRE_EOL();
                } else return cbf_configError_unexpectedInput;
            }
            GET_TOKEN();
        }
		return _cbf_config_validate(vec);
    }

	/*
	Helper function to take the data associated with a pilatus axis and write the
	axis attributes to a nexus axis.

	\return An error code
	*/
#ifdef CBF_USE_ULP
#define CBFM_pilatusAxis2nexusAxisAttrs(h4data,units,depends_on,exsisItem,cmp,cmp_params) \
_cbf_pilatusAxis2nexusAxisAttrs(h4data,units,depends_on,exsisItem,cmp,cmp_params)
#else
#define CBFM_pilatusAxis2nexusAxisAttrs(h4data,units,depends_on,exsisItem,cmp,cmp_params) \
_cbf_pilatusAxis2nexusAxisAttrs(h4data,units,depends_on,exsisItem,cmp)
#endif
	static int _cbf_pilatusAxis2nexusAxisAttrs
			(hid_t h5data,
			 const char * const units,
			 const char * const depends_on,
			 const cbf_configItem_t * const axisItem,
#ifdef CBF_USE_ULP
			 int (*cmp)(const void *, const void *, size_t, const void * const)
			 ,const void * const cmp_params
#else
			 int (*cmp)(const void *, const void *, size_t)
#endif
             )
	{
		int error = CBF_SUCCESS;
		CBF_CALL(cbf_H5Arequire_string(h5data,"units",strcmp(units, "deg.")?units:"degrees"));
		/* transformation type */
		CBF_CALL(cbf_H5Arequire_string(h5data,"transformation_type","rotation"));
		/* dependency */
		CBF_CALL(cbf_H5Arequire_string(h5data,"depends_on",depends_on));
		if (!axisItem->depends_on) {
			cbf_debug_print2("Error: missing dependency for nexus axis '%s'\n",axisItem->nexus);
			error |= CBF_UNDEFINED;
		}
		if (CBF_SUCCESS==error) { /* vector */
			const hsize_t vdims[] = {3};
			double buf[3] = {0./0.};
			double matrix[3][3] = {
				{-1.,0.0,0.0},
				{0.0,1.0,0.0},
				{0.0,0.0,-1.},
			};
			double vector[3];
			CBF_CALL(cbf_apply_matrix(matrix,(double *)axisItem->vector,vector));
			CBF_CALL(CBFM_H5Arequire_cmp2(h5data,"vector",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,vector,buf,cmp,cmp_params));
		}
		return error;
	}

    /****************************************************************
     End of section of code extracted from J. Sloan's
     config.c
     ****************************************************************/

	/*
	Simple wrapper function to create a nexus group.
	Forwards to cbf_H5Grequire and cbf_H5Arequire_string, letting them check argument validity.
	*/
	static int _cbf_NXGrequire
			(const hid_t location,
			 hid_t * const dataset,
			 const char * const name,
			 const char * const class)
	{
		int error = CBF_SUCCESS;
		hid_t dset = CBF_H5FAIL;
		cbf_reportnez(cbf_H5Grequire(location,&dset,name),error);
		cbf_reportnez(cbf_H5Arequire_string(dset,"NX_class",class),error);
		if (dataset) *dataset = dset;
		else cbf_H5Dfree(dset);
		return error;
	}

	/*
     Extract the NX_class attribute from a HDF5 object, returning it in 'class' as a string that must be free'd.
     */
	static int _cbf_NXclass
    (const hid_t object,
     const char * * const class)
	{
		int error = CBF_SUCCESS;
		/* check the arguments */
		if (!cbf_H5Ivalid(object) || !class) error |= CBF_ARGUMENT;
		if (CBF_SUCCESS==error) {
			/* check the NX_class attribute */
			hid_t attr = CBF_H5FAIL;
			const char attrName[] = "NX_class";
			const int found = cbf_H5Afind(object,&attr,attrName,CBF_H5FAIL,CBF_H5FAIL);
			if (CBF_SUCCESS!=found) {
				cbf_debug_print(cbf_strerror(found));
				error |= found;
			} else {
				error |= cbf_H5Aread_string(attr, class);
			}
			cbf_H5Afree(attr);
		}
		return error;
	}

	/* ************************************************************************
	Define a set of node manipulation functions which are missing from cbf's
     node tree interface. All to be removed and replaced with the regular
     routines they duplicate.  This level of access is error-prone and
     produces unclear code.
	************************************************************************ */

    /*
     Get the ascii value of a given row of a node, in the same way as 'cbf_get_value' gets data from a handle.
     */
	static int cbf_node_get_value
    (cbf_node * const node,
     const unsigned int row,
     const char * * const value)
	{
		int error = CBF_SUCCESS;
		const char * text = NULL;
		/* Check the arguments */
		if (!node || row >= node->children || !value) {
			error |= CBF_ARGUMENT;
		} else if (cbf_is_binary(node, row)) {
			error |= CBF_BINARY;
		} else if (CBF_SUCCESS!=(error|=cbf_get_columnrow(&text, node, row))) {
			cbf_debug_print2("error: %s\n", cbf_strerror(error));
		} else {
			*value = text ? text+1 : NULL;
		}
		return error;
	}

    static int cbf_node_get_doublevalue
    (cbf_node * const node,
     const unsigned int row,
     double * const value)
	{
		int error = CBF_SUCCESS;
		const char * text = NULL;
		if (!node || row >= node->children || !value) {
			error |= CBF_ARGUMENT;
		} else if (cbf_is_binary(node, row)) {
			error |= CBF_BINARY;
		} else if (CBF_SUCCESS!=(error|=cbf_get_columnrow(&text, node, row))) {
			cbf_debug_print2("error: %s\n",cbf_strerror(error));
		} else if (!text || *text==CBF_TOKEN_NULL) {
            *value = 0.;
            return CBF_SUCCESS;
		} else {
			char * end = NULL;
			const double tmp_val = strtod(text+1, &end);
			if (end == text+1) {
				cbf_debug_print2("error: %s\n", cbf_strerror(CBF_FORMAT));
                *value = 0.;
			} else {
				*value = tmp_val;
			}
		}
		return error;
	}

	/* Test for the presence of a floating-point value in a column.

	Attempt to access the value at the given column/row location and try to
	convert it to a floating point value, discarding the result and returning
	a boolean value which can be used to find out if a conversion would
	succeed.

	TODO: Merge this functionality into the 'cbf_node_get_doublevalue'
	function, to allow the test an conversion to be performed in a single
	operation.

	\return A boolean value suitable for use in a conditional statement.
	*/
	static int cbf_node_has_doublevalue
			(cbf_node * const node,
			 const unsigned int row)
	{
		int ret;
		const char * text = NULL;
		if (!node || row >= node->children) {
			ret = 0;
		} else if (cbf_is_binary(node, row)) {
			ret = 0;
		} else if (CBF_SUCCESS!=cbf_get_columnrow(&text, node, row)) {
			ret = 0;
		} else if (!text || *text==CBF_TOKEN_NULL) {
			ret = 0;
		} else {
			char * end = NULL;
			/* check if it can be converted, but don't store the value */
			(void)(strtod(text+1, &end));
			if (end == text+1) {
				ret = 0;
			} else {
				ret = 1;
			}
		}
		return ret;
	}

	static int cbf_node_get_uintvalue
			(cbf_node * const node,
			 const unsigned int row,
			 unsigned int * const value)
	{
		int error = CBF_SUCCESS;
		const char * text = NULL;
		if (!node || row >= node->children || !value) {
			error |= CBF_ARGUMENT;
		} else if (cbf_is_binary(node, row)) {
			error |= CBF_BINARY;
		} else if (CBF_SUCCESS!=(error|=cbf_get_columnrow(&text, node, row))) {
			cbf_debug_print2("error: %s\n", cbf_strerror(error));
		} else if (!text || *text==CBF_TOKEN_NULL) {
            *value = 0;
            return CBF_SUCCESS;
		} else {
			char * end = NULL;
			const unsigned int tmp_val = strtoul(text+1, &end, 0);
			if (end == text+1) {
				cbf_debug_print2("error: %s\n", cbf_strerror(CBF_FORMAT));
				error |= CBF_FORMAT;
                *value = 0;
			} else {
				*value = tmp_val;
			}
		}
		return error;
	}

	/*
	Search for a row with matching value, with the first to check being given by 'row'.
	If you want to find the first matching row in a column then set row to '0'.
	If you already have a matching row and want to find the next then set row to '1+matching_row'.
	*/
	static int cbf_node_find_nextrow
			(cbf_node * const node,
			 unsigned int row,
			 const char * const value,
			 unsigned int * const nextrow)
	{
		int error = CBF_SUCCESS;
		if (!nextrow || !node || !value) {
			error |= CBF_ARGUMENT;
		} else if (row >= node->children || CBF_COLUMN != node->type) {
			error |= CBF_ARGUMENT;
		} else {
			for (; row != node->children; ++row) {
				const char * str = NULL;
				cbf_node_get_value(node,row,&str);
				if (!strcmp(value,str)) {
					break;
				}
			}
			if (row == node->children) {
				error |= CBF_NOTFOUND;
			} else {
				*nextrow = row;
			}
		}
		return error;
	}

	/**
     Check the handle for the presence of a file, optionally returning it.
     \param nx A handle to query for the presence of the requested information.
     \param file A place to store the file (if found), or null if the file isn't wanted.
     \sa cbf_h5handle_get_file
     \sa cbf_h5handle_set_file
     \return An error code.
	 */
    int cbf_h5handle_get_file
    (const cbf_h5handle nx,
     hid_t * const file)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (file) {
				if (cbf_H5Ivalid(nx->hfile)) *file = nx->hfile;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}

	/**
     Sets the file id within the handle to the given value. Doesn't check or modify any attributes in any way.
     \param nx The handle to add information to.
     \param file The file to be set as the current file id.
     \sa cbf_h5handle_get_file
     \sa cbf_h5handle_set_file
     \return An error code.
     */
    int cbf_h5handle_set_file
    (const cbf_h5handle nx,
     const hid_t file)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(file)) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->hfile);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,file);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = file;
			}
		}
		return error;
	}
    
	/**
	Check the handle for the presence of an entry group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_entry
     \sa cbf_h5handle_set_entry
     \sa cbf_h5handle_require_entry
     \return An error code.
	 */
    int cbf_h5handle_get_entry
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
			} else {
			hid_t * const nxGroup = &(nx->nxid);
			const char * * const nxName = &(nx->nxid_name);
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(*nxGroup)) *group = *nxGroup;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (*nxName) *name = *nxName;
				else error |= CBF_NOTFOUND;
		}
	}
		return error;
	}

	/**
     Sets the entry group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current entry group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_entry
     \sa cbf_h5handle_set_entry
     \sa cbf_h5handle_require_entry
     \return An error code.
	 */
    int cbf_h5handle_set_entry
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxid);
			const char * * const nxName = &(nx->nxid_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
		return error;
	}

	/**
     This will check if the entry group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.

     \param nx The HDF5 handle to use.
	\param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"entry"</code>.
     \sa cbf_h5handle_get_entry
     \sa cbf_h5handle_set_entry
     \sa cbf_h5handle_require_entry
     \return An error code.
     */
	int cbf_h5handle_require_entry
    (const cbf_h5handle nx,
     hid_t * const group,
			 const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "entry";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_file(nx,&parent));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_entry(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXentry"));
				CBF_CALL(cbf_h5handle_set_entry(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_entry(nx,group,0));
		}
		return error;
	}

	/**
     This will check if the entry group and definition within the handle matches any 
     existing group of the same name within the current file and has a definition
     designation that agrees. If the group name doesn't match a new group is opened or created
     and added to the handle.  If the <code>definition</code> does not match, it is replaced with
     the new one.  If the <code>version</code> attribute does not match it is replaced with the
     new one.  If the <code>URL></code> attribute does not match it is replace with the new
     one. The <code>NX_class</code> attributes are not checked, but if a new entry
     is created it will be created with <code>NX_class</code> NXentry.
     
     \param nx The HDF5 handle to use.
     \param group An optional pointer to a place where the group ID should be stored.
     \param name The group name, or null to use the default name of <code>"entry"</code>.
     \param definition The definition name, or null to not specify a definition name.
     \param version The version string, or null to not specify a version string.
     \param URL The URL at which the definition is stored, or null to not specify a URL
     \sa cbf_h5handle_get_entry
     \sa cbf_h5handle_set_entry
     \sa cbf_h5handle_require_entry
     \return An error code.
     */
	int cbf_h5handle_require_entry_definition
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name,
     const char * definition,
     const char * version,
     const char * URL
     )
	{
        int matchgroup;  /* 0 for not found, 1 for matched, -1 for not matched*/
        int matchdefinition;  /* 0 for not found, 1 for matched, -1 for not matched*/
        int matchversion;  /* 0 for not found, 1 for matched, -1 for not matched*/
        int matchURL;  /* 0 for not found, 1 for matched, -1 for not matched*/
		int error = CBF_SUCCESS;

        hid_t type = CBF_H5FAIL;
        matchgroup = 0;
        matchdefinition = definition?0:1;
        matchversion = version?0:1;
        matchURL = URL?0:1;
        
        CBF_CALL(cbf_H5Tcreate_string(&type,H5T_VARIABLE));
        
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
            hid_t dataset = CBF_H5FAIL;
            hid_t attribute = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "entry";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_file(nx,&parent));
            
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_entry(nx,&curr_group,&curr_name)) {
				if (!cbf_cistrcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					if (CBF_SUCCESS==cbf_H5Gfind(parent,&test_group,group_name)) {
						if (!cbf_H5Ocmp(test_group,curr_group)) matchgroup = 1;
                        /* If we have the group and want the definition to match
                         search for the definition field */
                        if (matchgroup && (!matchdefinition)) {
                            if (CBF_SUCCESS==cbf_H5Dfind2(test_group,&dataset,"definition",0,0,0,type)){
                                const hid_t currType = H5Dget_type(dataset);
                                const char * buf = 0;
                                hid_t currMemType = CBF_H5FAIL;
                                cbf_H5Tcreate_string(&currMemType,H5T_VARIABLE);
                                cbf_H5Dread2(dataset,0,0,0,&buf,currMemType);
                                cbf_H5Tfree(currMemType);
                                /* then compare them */
                                if (cbf_cistrcmp(definition,buf) != 0) {
                                    CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&definition,type));
                                }
                                free((void*)buf);
                                cbf_H5Tfree(currType);
                            } else {
                                CBF_CALL(cbf_H5Dcreate(test_group,&dataset,"definition",0,0,0,0,type));
                                CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&definition,type));
                            }
                            /* The definition now matches, see if we want the version and/or URL */
                            if (!matchversion) {
                                CBF_CALL(cbf_H5Arequire_string(dataset,"version",version));
                            }
                            if (!matchURL) {
                                CBF_CALL(cbf_H5Arequire_string(dataset,"URL",URL));
                            }
                        }
					} else {
						matchgroup = 0;
					}
					cbf_H5Gfree(test_group);
      			}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !matchgroup) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXentry"));
				CBF_CALL(cbf_h5handle_set_entry(nx,new_group,group_name));
                if (!matchdefinition) {
                    CBF_CALL(cbf_H5Dcreate(new_group,&dataset,"definition",0,0,0,0,type));
                    CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&definition,type));
                    if (!matchversion) {
                        CBF_CALL(cbf_H5Arequire_string(dataset,"version",version));
                    }
                    if (!matchURL) {
                        CBF_CALL(cbf_H5Arequire_string(dataset,"URL",URL));
                    }
                }
				if (CBF_SUCCESS!=error) {
                    cbf_H5Gfree(new_group);
                }
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_entry(nx,group,0));
            cbf_H5Tfree(type);
            cbf_H5Dfree(dataset);
            cbf_H5Afree(attribute);
		}
		return error;
	}

    
	/**
     Check the handle for the presence of an sample group and its name, optionally returning any combination of them.
     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_sample
     \sa cbf_h5handle_set_sample
     \sa cbf_h5handle_require_sample
     \return An error code.
	 */
	int cbf_h5handle_get_sample
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
			int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxsample)) *group = nx->nxsample;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxsample_name) *name = nx->nxsample_name;
				else error |= CBF_NOTFOUND;
			}
		}
			return error;
	}
    
	/**
     Sets the sample group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current sample group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_sample
     \sa cbf_h5handle_set_sample
     \sa cbf_h5handle_require_sample
     \return An error code.
	 */
	int cbf_h5handle_set_sample
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxsample);
			const char * * const nxName = &(nx->nxsample_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
		return error;
	}

	/**
     This will check if the sample group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.

     \param nx The HDF5 handle to use.
	\param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"sample"</code>.
     \sa cbf_h5handle_get_sample
     \sa cbf_h5handle_set_sample
     \sa cbf_h5handle_require_sample
     \return An error code.
     */
	int cbf_h5handle_require_sample
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "sample";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_entry(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_sample(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXsample"));
				CBF_CALL(cbf_h5handle_set_sample(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_sample(nx,group,0));
		}
		return error;
	}
    
	/**
	Check the handle for the presence of a beam group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_beam
     \sa cbf_h5handle_set_beam
     \sa cbf_h5handle_require_beam
     \return An error code.
	 */
	int cbf_h5handle_get_beam
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
			int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxbeam)) *group = nx->nxbeam;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxbeam_name) *name = nx->nxbeam_name;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}
    
	/**
     Sets the beam group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current beam group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_beam
     \sa cbf_h5handle_set_beam
     \sa cbf_h5handle_require_beam
     \return An error code.
	 */
	int cbf_h5handle_set_beam
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxbeam);
			const char * * const nxName = &(nx->nxbeam_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
	}
		}
		return error;
	}

	/**
     This will check if the beam group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.

     \param nx The HDF5 handle to use.
	\param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"beam"</code>.
     \sa cbf_h5handle_get_beam
     \sa cbf_h5handle_set_beam
     \sa cbf_h5handle_require_beam
     \return An error code.
	 */
	int cbf_h5handle_require_beam
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "beam";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_sample(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_beam(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXbeam"));
				CBF_CALL(cbf_h5handle_set_beam(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_beam(nx,group,0));
		}
		return error;
	}

	/**
	Check the handle for the presence of an instrument group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_instrument
     \sa cbf_h5handle_set_instrument
     \sa cbf_h5handle_find_instrument
     \sa cbf_h5handle_require_instrument
     \return An error code.
     */
	int cbf_h5handle_get_instrument
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxinst)) *group = nx->nxinst;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxinstrument_name) *name = nx->nxinstrument_name;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}
    
	/**
     Sets the instrument group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current instrument group
     \param name The name which the group should be given.

     \sa cbf_h5handle_get_instrument
     \sa cbf_h5handle_set_instrument
     \sa cbf_h5handle_find_instrument
     \sa cbf_h5handle_require_instrument

     \return An error code.
	 */
	int cbf_h5handle_set_instrument
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
			int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxinst);
			const char * * const nxName = &(nx->nxinstrument_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
		return error;
	}

	/* TODO: add a 'find NXgroup' function, instead of relying on pre-set group names here */

	/**
     This will check if the instrument group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.

     \param nx The HDF5 handle to use.
	\param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"instrument"</code>.

     \sa cbf_h5handle_get_instrument
     \sa cbf_h5handle_set_instrument
	 \sa cbf_h5handle_find_instrument
     \sa cbf_h5handle_require_instrument

     \return An error code.
	 */
	int cbf_h5handle_require_instrument
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "instrument";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_entry(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_instrument(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXinstrument"));
				CBF_CALL(cbf_h5handle_set_instrument(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_instrument(nx,group,0));
		}
		return error;
	}

	/**
     Check the handle for the presence of a detector group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_detector
     \sa cbf_h5handle_set_detector
     \sa cbf_h5handle_find_detector
     \sa cbf_h5handle_require_detector
     \return An error code.
     */
	int cbf_h5handle_get_detector
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
            if (nx->num_detectors < 1 || nx->cur_detector >= nx->num_detectors) {
                return CBF_NOTFOUND;
            }
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxdetectors[nx->cur_detector])) *group = nx->nxdetectors[nx->cur_detector];
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxdetector_names[nx->cur_detector]) *name = nx->nxdetector_names[nx->cur_detector];
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}
    
	/**
     Sets the detector group and name within the handle to the given values.
     
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current detector group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_detector
     \sa cbf_h5handle_set_detector
     \sa cbf_h5handle_find_detector
     \sa cbf_h5handle_require_detector
     \return An error code.
	 */
	int cbf_h5handle_set_detector
    (const cbf_h5handle nx,
     const hid_t group,
			 const char * const name)
	{
        int ii;
        int match;
		int error = CBF_SUCCESS;
        void * nameblock;
        nameblock = (void *)(nx->nxdetector_names);
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
            return error;
        }
        
        /* See if there is a match on name */
        
        match = 0;
        for (ii = 0; ii < nx->num_detectors; ii++) {
            if (!cbf_cistrcmp(name,nx->nxdetector_names[ii])) {
                nx->cur_detector = ii;
                match = 1;
                break;
            }
        }
        if (!match) {
            /*  There is no matching name, we need to find or create
             a new slot */
            if (nx->nxdetectors == NULL){
                cbf_failnez(cbf_alloc(((void **) &(nx->nxdetectors)),NULL,
                                      sizeof(hid_t),10));
                cbf_onfailnez(cbf_alloc(((void **) &(nx->nxdetector_names)),NULL,
                                        sizeof(char *),10),cbf_free(&(nameblock),NULL));
                for (ii = 0; ii < 10; ii ++) {
                    nx->nxdetectors[ii] = (hid_t)CBF_H5FAIL;
                    nx->nxdetector_names[ii] = NULL;
                }
                nx->num_detectors = 0;
                nx->cap_detectors = 10;
                nx->cur_detector = 0;
            }
            if (nx->num_detectors >= nx->cap_detectors ) {
                unsigned int newcap = 2*nx->cap_detectors;
                unsigned int oldcap = nx->cap_detectors;
                hid_t * oldnxdetectors = nx->nxdetectors;
                const char ** oldnxdetector_names = nx->nxdetector_names;
                void * oldnxdmap = (void *)nx->nxdetectors;
                void * oldnxdnmap = (void *)nx->nxdetector_names;
                cbf_failnez(cbf_alloc(((void **) &(nx->nxdetectors)),NULL,
                                      sizeof(hid_t),newcap));
                cbf_onfailnez(cbf_alloc(((void **) &(nx->nxdetector_names)),NULL,
                                        sizeof(char *),newcap),cbf_free(&(nameblock),NULL));
                for (ii = 0; ii < newcap; ii ++) {
                    if (ii < oldcap) {
                        nx->nxdetectors[ii] = oldnxdetectors[ii];
                        nx->nxdetector_names[ii] = oldnxdetector_names[ii];
                    } else {
                        nx->nxdetectors[ii] = (hid_t)CBF_H5FAIL;
                        nx->nxdetector_names[ii] = NULL;
                    }
                }
                nx->cap_detectors = newcap;
                if (oldcap && oldnxdetectors) {
                    cbf_free(&oldnxdmap,NULL);
                    cbf_free(&oldnxdnmap,NULL);
                }
            }
            nx->cur_detector = nx->num_detectors;
            (nx->num_detectors)++;
            
        }
        
        
        
        {
			hid_t * const nxGroup = &(nx->nxdetectors[nx->cur_detector]);
			const char * * const nxName = &(nx->nxdetector_names[nx->cur_detector]);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
            }
		}
		return error;
	}
    
	/**
     This will check if the detector group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.
     
     \param nx The HDF5 handle to use.
     \param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"detector"</code>.
     \sa cbf_h5handle_get_detector
     \sa cbf_h5handle_set_detector
     \sa cbf_h5handle_find_detector
     \sa cbf_h5handle_require_detector
     \return An error code.
	 */
	int cbf_h5handle_require_detector
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
        int ii;
        unsigned int save_cur_detector;
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char default_name[] = "detector";
			const char * group_name = name ? name : default_name;
            hid_t test_group = CBF_H5FAIL;
            hid_t cur_group = CBF_H5FAIL;
            const char * cur_name = NULL;
            int found;
            if (nx->nxdetectors&&nx->num_detectors>0&&!name&&!group){
                nx->cur_detector = 0;
                return error;
            }
            if (nx->nxdetectors&&nx->num_detectors>0&&!name&&group&&!cbf_H5Ivalid(*group)){
                *group = nx->nxdetectors[0];
                return error;
            }
			CBF_CALL(cbf_h5handle_get_instrument(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
            if (error==CBF_SUCCESS &&((group!=NULL && cbf_H5Ivalid(*group)) || name!=NULL)) {
                save_cur_detector = nx->cur_detector;
                for (ii = 0; ii < nx->num_detectors; ii++) {
                    cur_group = nx->nxdetectors[ii];
                    cur_name = nx->nxdetector_names[ii];
                    if (nx->nxdetector_names[ii] && !cbf_cistrcmp(group_name,nx->nxdetector_names[ii])){
                        if (group == NULL || !cbf_H5Ivalid(*group)) {
                            nx->cur_detector = ii;
                            if (group) *group = cur_group;
                            return CBF_SUCCESS;
                        }
                        found = cbf_H5Gfind(parent,&test_group,group_name);
                        if (found == CBF_SUCCESS){
                            if (!cbf_H5Ocmp(test_group,curr_group)) {
                                nx->cur_detector = ii;
                                cbf_H5Gfree(test_group);
                                if (group) *group = cur_group;
                                return CBF_SUCCESS;
                            } else {
                                error |= found;
                                cbf_H5Gfree(test_group);
                                nx->cur_detector = save_cur_detector;
                                break;
                            }
                        }
                    }
                }
            }
            
            /* One of the following holds:
               1.  We failed to find the instrument -- leave now with an error
               2.  We specified a group,  but the name did not match
               3.  We specified a group, the name matched, but the group didn't
               4.  We specified a group that did not match
               5.  We did not specify a group
               In cases 2 -- 5, we need to create a new detector group with the
               name specified and add it as a new detector.  If the same matches
               it goes into that slot, otherwise into a new slot.
             */
			if (CBF_SUCCESS==error) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXdetector"));
				CBF_CALL(cbf_h5handle_set_detector(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_detector(nx,group,0));
		}
		return error;
	}
    
    
    /*
     Decompress the data selected in the handle, ensure an appropriate
     HDF5 dataset exists to store it, insert it a the given index with
     some parameter values set according to the given flags.
     
     Writes saturation_value, undefined_value and data to parent if
     requested.
     */
    static int cbf_write_array_h5file2(const cbf_node * node,
                                       const unsigned int row,
                                       const cbf_h5handle h5handle,
                                       const char * arrayid,
                                       const char * binaryid,
                                       const char * saturation_value,
                                       const char * undefined_value,
                                       const char * details,
                                       const char * gain,
                                       const char * gain_esd,
                                       const char * linearity,
                                       const char * offset,
                                       const char * scaling,
                                       const char * overload,
                                       const hid_t parent)
    {
        int error = CBF_SUCCESS;
        
        const char * datasetname;
        
        const char * datasetname_parts[4] = {
            "data",
            arrayid,
            binaryid,
            0
        };
        
        
        cbf_debug_print("write_array_h5file\n");
        
        datasetname = _cbf_strjoin(datasetname_parts,'_');
        
        if (!node) {
            cbf_debug_print("Invalid node given\n");
            error |= CBF_ARGUMENT;
        } else if (!h5handle) {
            cbf_debug_print("Invalid hdf5 handle given\n");
            error |= CBF_ARGUMENT;
        } else if (datasetname){
            int found = CBF_SUCCESS, id, bits, sign, real;
            cbf_file *file;
            long start;
            const char *byteorder;
            size_t size, nelem, cbfdim[3], padding;
            unsigned int compression;
            hid_t h5type = CBF_H5FAIL;
            
            
            /* find the datatype and array size */
            CBF_CALL(cbf_get_bintext(node, row, NULL,
                                     &id, &file, &start, &size,
                                     NULL, NULL, &bits, &sign, &real,
                                     &byteorder, &nelem, cbfdim+2, cbfdim+1, cbfdim+0, &padding,
                                     &compression));
            CBF_CALL(cbf_find_array_data_h5type(&h5type,bits,sign,real,byteorder));

            
            
            /* allocate space for the decompressed data */
            if (CBF_SUCCESS == error) {
                void * value;
                const unsigned int elsize = (bits+7)/8;
                size_t nelem_read;
                const int rank = 3;
                hsize_t buf[] = {0, 0, 0};
                hsize_t h5dim[] = {0, cbfdim[1], cbfdim[2]};
                hsize_t h5max[] = {H5S_UNLIMITED, cbfdim[1], cbfdim[2]};
                hsize_t h5chunk[] = {1, cbfdim[1], cbfdim[2]};
                hid_t dset = CBF_H5FAIL;
                value = malloc(nelem*elsize);
                CBF_CALL(cbf_set_fileposition(file, start, SEEK_SET));
                CBF_CALL(cbf_decompress_parameters(NULL, NULL, NULL, NULL, NULL, NULL, NULL, compression, file));
                {
                    cbf_debug_print2("masked compression: %d\n",compression&CBF_COMPRESSION_MASK);
                    cbf_debug_print("compression type: ");
                    if (compression == CBF_CANONICAL) {
                        cbf_debug_print("CBF_CANONICAL\n");
                    } else if ((compression&CBF_COMPRESSION_MASK) == CBF_PACKED){
                        cbf_debug_print("CBF_PACKED\n");
                    } else if ((compression&CBF_COMPRESSION_MASK) == CBF_PACKED_V2) {
                        cbf_debug_print("CBF_PACKED_V2\n");
                    } else if (compression == CBF_BYTE_OFFSET) {
                        cbf_debug_print("CBF_BYTE_OFFSET\n");
                    } else if (compression == CBF_NIBBLE_OFFSET) {
                        cbf_debug_print("CBF_NIBBLE_OFFSET\n");
                    } else if (compression == CBF_PREDICTOR) {
                        cbf_debug_print("CBF_PREDICTOR\n");
                    } else if (compression == CBF_NONE) {
                        cbf_debug_print("CBF_NONE\n");
                    } else {
                        cbf_debug_print("Unknown\n");
                    }
                    cbf_debug_print2("element size: %d\n",(unsigned int)(elsize));
                    cbf_debug_print2("real?: %s\n",real?"yes":"no");
                }
                
                /* ensure a dataset exists in the detector */
                found =  cbf_H5Dfind2(parent,
                                      &dset,datasetname,rank,h5max,buf,h5type);
                if (CBF_SUCCESS==found) {
                } else if (CBF_NOTFOUND==found) {
                    /* define variables & check args */
                    hid_t dataSpace = CBF_H5FAIL;
                    hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
                    
                    /* check variables are valid */
                    CBF_CALL(cbf_H5Screate(&dataSpace, rank, h5dim, h5max));
                    
                    /* allow dataset to be chunked */
                    CBF_H5CALL(H5Pset_chunk(dcpl,rank,h5chunk));
                    /* allow compression */
                    if (CBF_SUCCESS==error) {
                        if (h5handle->flags & CBF_H5COMPRESSION_ZLIB) {
                            H5Pset_deflate(dcpl, 1);
                        } else if (h5handle->flags & CBF_H5COMPRESSION_CBF) {
                            unsigned int cd_values[CBF_H5Z_FILTER_CBF_NELMTS];
                            cd_values[CBF_H5Z_FILTER_CBF_COMPRESSION] = compression;
                            cd_values[CBF_H5Z_FILTER_CBF_RESERVED]    = 0;
                            cd_values[CBF_H5Z_FILTER_CBF_BINARY_ID]   = id;
                            cd_values[CBF_H5Z_FILTER_CBF_PADDING]     = padding;
                            cd_values[CBF_H5Z_FILTER_CBF_ELSIZE]      = elsize;
                            cd_values[CBF_H5Z_FILTER_CBF_ELSIGN]      = sign;
                            cd_values[CBF_H5Z_FILTER_CBF_REAL]        = real;
                            cd_values[CBF_H5Z_FILTER_CBF_DIMFAST]     = *(h5chunk+2);
                            cd_values[CBF_H5Z_FILTER_CBF_DIMMID]      = *(h5chunk+1);
                            cd_values[CBF_H5Z_FILTER_CBF_DIMSLOW]     = *(h5chunk+0);
                            
                            if (h5handle->flags & CBF_H5_REGISTER_COMPRESSIONS) {
                                if (!H5Zfilter_avail(CBF_H5Z_FILTER_CBF)) {
                                    CBF_H5CALL(H5Zregister(CBF_H5Z_CBF));
                                }
                            }
                            
                            CBF_H5CALL(H5Pset_filter(dcpl, CBF_H5Z_FILTER_CBF, H5Z_FLAG_OPTIONAL, CBF_H5Z_FILTER_CBF_NELMTS, cd_values));
                            
                        }
                    }
                    
                    /* create the dataset */
                    if (CBF_SUCCESS == error)
                        dset = H5Dcreate2(parent,datasetname,h5type,dataSpace,H5P_DEFAULT,dcpl,H5P_DEFAULT);
                    
                    /* check local variables are properly closed */
                    if (cbf_H5Ivalid(dataSpace)) H5Sclose(dataSpace);
                    if (cbf_H5Ivalid(dcpl)) H5Pclose(dcpl);
                } else {
                    error |= found;
                    cbf_debug_print2("error locating primary dataset: %s\n", cbf_strerror(found));
                }
                if (CBF_SUCCESS==error) {
                    const hsize_t h5offset[] = {h5handle->slice, 0, 0};
                    const int sig[] = {1};
                    int sigbuf[] = {0};
                    
                    /* extract the image data from CBF */
                    CBF_CALL(cbf_decompress(value, elsize, sign, nelem, &nelem_read,
                                            size, compression, bits, sign, file, real, byteorder,
                                            nelem, cbfdim[2], cbfdim[1], cbfdim[0], padding));
                    if (nelem_read != nelem) error |= CBF_ENDOFDATA;
                    
                    /* store the image data in HDF5 */
                    CBF_CALL(cbf_H5Dinsert(dset,h5offset,0,h5chunk,buf,value,h5type));
                    CBF_CALL(CBFM_H5Arequire_cmp2(dset,"signal",0,0,H5T_STD_I32LE,H5T_NATIVE_INT,sig,sigbuf,cmp_int,0));
                    if (arrayid){
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "array_id",
                                                         arrayid,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (binaryid){
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "binary_id",
                                                         binaryid,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (details) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "details",
                                                         details,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (gain) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "gain",
                                                         gain,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (gain_esd) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "gain_esd",
                                                         gain_esd,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (linearity) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "linearity",
                                                         linearity,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (offset) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "offset",
                                                         offset,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (scaling) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "scaling",
                                                         scaling,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (overload) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "saturation_value",
                                                         overload,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    if (undefined_value) {
                    CBF_CALL(cbf_add_h5text_attribute_slab(dset, parent,
                                                         "undefined_value",
                                                         undefined_value,
                                                         NULL, datasetname+5,
                                                         (hsize_t) (h5handle->slice),
                                                         error));
                    }
                    

                    free((void*)datasetname);
                    cbf_H5Dfree(dset);
                    free((void*)value);
                }
            }
        }
        
        return error;
    }

    
    /* Find row by multiple columns
         n is the number of columns
         column is an array of n column names
         value is an array of values to match
     
     */
    
    int cbf_find_row_by_columns(cbf_handle handle, int n,
                                const char * column[],
                                const char * value[]){
        
        int icol;
        
        int match;
        
        const char *colvalue;
        
        if (!handle || n < 1
            || !column || !value
            || !column[0] || !value[0]) return CBF_ARGUMENT;
        
        cbf_failnez(cbf_rewind_row(handle));
        
        while (!cbf_find_column(handle,column[0])
               &&!cbf_find_nextrow(handle,value[0])) {
            
            match = 1;
            
            for (icol = 1; icol < n; icol++) {
                
                if ( !column[icol] || !value[icol] ) return CBF_ARGUMENT;
                
                cbf_failnez(cbf_find_column(handle,column[icol]));
                
                if (cbf_get_value(handle,&colvalue)
                    || !colvalue
                    || cbf_cistrcmp(colvalue,value[icol])) {
                    
                    match = 0;
                    
                    break;
                    
                }
                
            }
            
            if (match) return CBF_SUCCESS;
            
        }
        
        return CBF_NOTFOUND;
        
    };
    
    

    /* Process the array id related fields for a given nxdata */
    
    int cbf_require_nxarrayid(const cbf_handle handle,
                              const cbf_h5handle h5handle,
                              const char * array_id,
                              hid_t nxdata) {
        
        const char * axis_set_id;
        
        const char * axis_id;
        
        const char * xarray_id;
        
        const char * xarray_section_id;
        
        const char * axis_indices;
        
        const char * axis_path;
        
        const char * axis_indices_parts[3];
        
        htri_t alexists;
        
        int error = 0;
        
        unsigned int row, rows;
        
        int array_id_found;
        
        
        
        
        int precedence;
        
        if (!handle
            || !h5handle
            || !array_id
            || !cbf_H5Ivalid(nxdata) ) return CBF_ARGUMENT;
        
        if (!cbf_find_category(handle,"array_structure_list")
            && !cbf_find_column(handle,"array_id")
            && !cbf_count_rows(handle,&rows)) {
            
            for (row = 0; row < rows; row++) {
                
                cbf_failnez(cbf_find_category(handle,"array_structure_list"));
                
                if (cbf_find_column(handle,"array_id")) {
                    
                    cbf_failnez(cbf_find_column(handle,"array_section_id"));
                    
                }
                
                cbf_failnez(cbf_select_row(handle,row));
                
                array_id_found = 0;
                
                if (!cbf_find_column(handle,"array_id")
                    && !cbf_get_value(handle,&xarray_id)
                    && xarray_id
                    && (!cbf_cistrcmp(xarray_id,array_id)
                        || !cbf_cistrcmp("None",array_id))){
                    
                    array_id_found = 1;
                    
                    
                } else {
                    
                    if (!cbf_find_column(handle,"array_section_id")
                        && !cbf_get_value(handle,&xarray_section_id)
                        && xarray_section_id
                        && !cbf_get_array_section_array_id(handle,xarray_section_id,&xarray_id)
                        && (!cbf_cistrcmp(xarray_id,array_id)
                            || !cbf_cistrcmp("None",array_id))){
                        
                        array_id_found = 1;
                        
                    }
                    
                }
                
                if (!array_id_found) continue;
                
                cbf_failnez(cbf_find_category(handle,"array_structure_list"));
                
                if (cbf_find_column(handle,"array_id")) {
                    
                    cbf_failnez(cbf_find_column(handle,"array_section_id"));
                    
                }
                
                cbf_failnez(cbf_select_row(handle,row));
                
                if (!cbf_find_column(handle,"axis_set_id")
                    && !cbf_get_value(handle,&axis_set_id)
                    && axis_set_id
                    && !cbf_find_column(handle,"precedence")
                    && !cbf_get_integervalue(handle,&precedence)
                    && !cbf_find_category(handle,"array_structure_list_axis")
                    && !cbf_find_column(handle,"axis_set_id")
                    && !cbf_find_row(handle,axis_set_id)
                    && !cbf_rewind_row(handle)) {
                    
                    while(!cbf_find_nextrow(handle,axis_set_id)) {
                        
                        cbf_failnez(cbf_find_column(handle,"axis_id"));
                        
                        cbf_failnez(cbf_get_value(handle,&axis_id));
                        
                        axis_indices_parts[0] = axis_id;
                        
                        axis_indices_parts[1] = "indices";
                        
                        axis_indices_parts[2] = 0;
                        
                        axis_indices = _cbf_strjoin(axis_indices_parts,'_');
                        
                        error |=
                        cbf_apply_h5integer_attribute(nxdata,axis_indices,precedence-1,error);
                        
                        free((void*)axis_indices);
                        
                        cbf_failnez(cbf_get_NX_axis_path(h5handle,axis_id,&axis_path))
                        
                        if (error) return error;
                        
                        alexists = H5Lexists(nxdata, axis_id, H5P_DEFAULT);
                        
                        if (alexists < 0 || !alexists) {
                            
                            cbf_h5reportneg(H5Lcreate_soft(axis_path,nxdata,axis_id,H5P_DEFAULT, H5P_DEFAULT),CBF_FORMAT,error);
                            
                        }
                        
                        cbf_failnez(cbf_find_column(handle,"axis_set_id"));
                        
                    }
                    
                }
                
                
            }
            
            return CBF_SUCCESS;
            
        } else {
            
            return CBF_NOTFOUND;
        }
        
    }
    
    /* process the data in a CBF looking for all combinations of array_ids
       and binary_ids for the given detector element and storing the
       data in data_ARRAYID_BINARYID:NXdata groups
     
       There are two choices on where to actually store the data;
          1.  Directly in NXdata, with an incoming link from NXdetector
          2.  Directly in NXdetector, with an incoming link from NXdetector
        and for each of those choices, with external links from the
        equivalent locations in a master h5handle.  If a master h5handle
        is given, the data h5handle NXdata or NXdetector that does not
        have the data will not be created here.
     
       If no detector_element is given, a special pseudo detector
       _NO_DETECTOR_ is used.
     
     */
    
    
    int cbf_require_nxdata(const cbf_handle handle,
                           const cbf_h5handle data_h5handle,
                           const cbf_h5handle master_h5handle,
                           const char * detector_element,
                           const int store_in_NXdata) {
        
        unsigned int row, rows;
        
        
        const char * nxdataname;
        
        const char * nxdetector;
        
        const char * datafilename;
        
        const char * abdetelid;
        
        const char * arrayid = NULL;
        
        const char * binaryid = NULL;
        
        const char * saturation_value = NULL;
        
        const char * undefined_value = NULL;
        
        const char * details = NULL;
        
        const char * gain = NULL;
        
        const char * gain_esd = NULL;
        
        const char * linearity = NULL;
        
        const char * offset = NULL;
        
        const char * scaling = NULL;
        
        const char * overload = NULL;
        
        const char * searchcols[] = {"array_id", "binary_id"};
        
        const char * values[] = {arrayid, binaryid};
        
        hid_t data_instrumentid;
        
        hid_t master_instrumentid;
        
        hid_t data_detectorid;
        
        hid_t master_detectorid;
        
        hid_t data_dataid;
        
        hid_t master_dataid;
        
        int error = 0;
        
        if (!handle || !data_h5handle ) return CBF_ARGUMENT;
        
        nxdetector = detector_element?detector_element:"_NO_DETECTOR_";
        
        data_instrumentid = master_instrumentid = CBF_H5FAIL;
        
        data_detectorid   = master_detectorid   = CBF_H5FAIL;
        
        data_dataid       = master_dataid       = CBF_H5FAIL;
        
        if (master_h5handle) {
            
            /* require an NXinstrument group and an NXdetector*/
            
            
            cbf_failnez(cbf_h5handle_require_instrument(master_h5handle,
                                                        &master_instrumentid,0));
            
            
            cbf_failnez(cbf_require_nxgroup(master_h5handle,
                                            nxdetector, "NXdetector",
                                            master_h5handle->nxinst, &master_detectorid));
            
        }
        
        if (!master_h5handle || !store_in_NXdata) {
            
            /* require an NXinstrument group and an NXdetector*/
            
            
            cbf_failnez(cbf_h5handle_require_instrument(data_h5handle,
                                                        &data_instrumentid,0));
            
            
            cbf_failnez(cbf_require_nxgroup(data_h5handle,
                                            nxdetector, "NXdetector",
                                            data_h5handle->nxinst, &data_detectorid));
            
        }
        
        cbf_failnez(cbf_find_category(handle,"array_data"));
        
        cbf_failnez(cbf_count_rows(handle,&rows));
        
        for (row = 0; row < rows; row ++) {
            
            int matchfound;
            
            const cbf_node * node;
            
            cbf_failnez(cbf_find_category(handle,"array_data"));
            
            if (cbf_find_column(handle,"array_id")
                ||cbf_select_row(handle,row)
                ||cbf_get_value(handle,&arrayid)
                || !arrayid) arrayid = "None";
            
            if (cbf_find_column(handle,"binary_id")
                ||cbf_select_row(handle,row)
                ||cbf_get_value(handle,&binaryid)
                || !binaryid) binaryid = "1";
            
            if (!cbf_find_column(handle,"data")) {
                
                node = handle->node;
                
            }
            
            /* See if this array_id and binary_id are
             for this detector_element */
            
            matchfound = 0;
            
            if ((!cbf_find_category(handle,"diffrn_data_frame")
                 || !cbf_find_category(handle,"diffrn_frame_data"))
                && !cbf_find_column(handle,"array_id")
                && !cbf_find_column(handle,"binary_id")
                && !cbf_find_column(handle,"detector_element_id")
                && !cbf_find_row_by_columns(handle,2,searchcols,values)) {
                
                if (cbf_find_column(handle,"detector_element_id")
                    ||cbf_get_value(handle,&abdetelid)
                    ||!abdetelid) abdetelid = "no_detector_element_id";
                
                if (!detector_element) {
                    
                    if (cbf_cistrcmp(abdetelid,"no_detector_element_id")) {
                        
                        matchfound = 1;
                        break;
                    }
                    
                    
                } else {
                    
                    if (!cbf_cistrcmp(abdetelid,detector_element)) {
                        
                        matchfound = 1;
                        break;
                    }
                    
                }
                
            } else {
                
                
                matchfound = 1;
                
            }
            
            if (!matchfound) continue;
            
            
            {
                const char * nxdatanameparts [] = {
                    "data",
                    arrayid,
                    binaryid,
                    0
                };
                
                
                if (!cbf_find_category(handle,"array_intensities")
                    &&!cbf_find_row_by_columns(handle,2,searchcols,values)){
                    
                    if (cbf_find_column(handle,"saturation_value")
                        || cbf_get_value(handle,&saturation_value))
                        saturation_value = NULL;
                    
                    if (cbf_find_column(handle,"undefined_value")
                        || cbf_get_value(handle,&undefined_value))
                        undefined_value = NULL;
                    
                    if (cbf_find_column(handle,"details")
                        || cbf_get_value(handle,&details))
                        details = NULL;
                    
                    if (cbf_find_column(handle,"gain")
                        || cbf_get_value(handle,&gain))
                        gain = NULL;
                    
                    if (cbf_find_column(handle,"gain_esd")
                        || cbf_get_value(handle,&gain_esd))
                        gain_esd = NULL;
                    
                    if (cbf_find_column(handle,"linearity")
                        || cbf_get_value(handle,&linearity))
                        linearity = NULL;
                    
                    if (cbf_find_column(handle,"offset")
                        || cbf_get_value(handle,&offset))
                        offset = NULL;
                    
                    if (cbf_find_column(handle,"scaling")
                        || cbf_get_value(handle,&scaling))
                        scaling = NULL;
                    
                    if (cbf_find_column(handle,"overload")
                        || cbf_get_value(handle,&overload))
                        overload = NULL;
                    
                    if (cbf_find_column(handle,"undefined_value")
                        || cbf_get_value(handle,&undefined_value))
                        undefined_value = NULL;
                    
                    
                }
                
                nxdataname = _cbf_strjoin(nxdatanameparts,'_');
                
                if (master_h5handle) {
                    
                    if (!cbf_H5Ivalid(master_h5handle->nxdata)) {
                        
                        error |= cbf_H5Grequire(master_h5handle->nxid,&master_dataid,nxdataname);
                        
                        error |= cbf_H5Arequire_string(master_dataid,"NX_class","NXdata");
                        
                    }
                    
                    if (store_in_NXdata) {
                        
                        if (!cbf_H5Ivalid(data_h5handle->nxdata)) {
                            
                            error |= cbf_H5Grequire(data_h5handle->nxid,&data_dataid,nxdataname);
                            
                            error |= cbf_H5Arequire_string(data_dataid,"NX_class","NXdata");
                            
                        }
                        
                        error |= cbf_write_array_h5file2(node,row,data_h5handle,
                                                         arrayid,
                                                         binaryid,
                                                         saturation_value,
                                                         undefined_value,
                                                         details,
                                                         gain,
                                                         gain_esd,
                                                         linearity,
                                                         offset,
                                                         scaling,
                                                         overload,
                                                         data_dataid);
                        
                        /* need to set up links
                         master_h5handle/entry/instrument/detector/data_arrayid_binaryid
                         --> master_h5handle/entry/data_arrayid_binaryid/data_arrayid_binaryid
                         master_h5handle/entry/data_arrayid_binaryid/data_arrayid_binaryid
                         --> data_h5handle/entry/data_arrayid_binaryid/data_arrayid_binaryid
                         need to set up axes in
                         master_h5handle/entry/data_arrayid_binaryid/
                         */
                        
                        
                    } else {
                        
                        
                        error |= cbf_write_array_h5file2(node,row,data_h5handle,
                                                         arrayid,
                                                         binaryid,
                                                         saturation_value,
                                                         undefined_value,
                                                         details,
                                                         gain,
                                                         gain_esd,
                                                         linearity,
                                                         offset,
                                                         scaling,
                                                         overload,
                                                         data_detectorid);
                        
                        /* need to set up links
                         master_h5handle/entry/data_arrayid_binaryid/data_arrayid_binaryid
                         --> master_h5handle/entry/instrument/detector/data_arrayid_binaryid
                         master_h5handle/entry/instrument/detector/data_arrayid_binaryid
                         --> data_h5handle/entry/instrument/detector/data_arrayid_binaryid
                         need to set up axes in
                         master_h5handle/entry/data_arrayid_binaryid/
                         */
                        
                    }
                    
                    
                    
                } else {
                    
                    if (!cbf_H5Ivalid(data_h5handle->nxdata)) {
                        
                        error |= cbf_H5Grequire(data_h5handle->nxid,&data_dataid,nxdataname);
                        
                        error |= cbf_H5Arequire_string(data_dataid,"NX_class","NXdata");
                        
                    }
                    
                    if (store_in_NXdata) {
                        
                        error |= cbf_write_array_h5file2(node,row,data_h5handle,
                                                         arrayid,
                                                         binaryid,
                                                         saturation_value,
                                                         undefined_value,
                                                         details,
                                                         gain,
                                                         gain_esd,
                                                         linearity,
                                                         offset,
                                                         scaling,
                                                         overload,
                                                         data_dataid);
                        
                        /* need to set up links
                         data_h5handle/entry/instrument/detector/data_arrayid_binaryid
                         --> data_h5handle/entry/data_arrayid_binaryid/data_arrayid_binaryid
                         
                         */
                        
                    } else {
                        
                        
                        error |= cbf_write_array_h5file2(node,row,data_h5handle,
                                                         arrayid,
                                                         binaryid,
                                                         saturation_value,
                                                         undefined_value,
                                                         details,
                                                         gain,
                                                         gain_esd,
                                                         linearity,
                                                         offset,
                                                         scaling,
                                                         overload,
                                                         data_detectorid);
                        
                        
                        
                    }
                    
                    error|= cbf_require_nxarrayid(handle,data_h5handle,arrayid,data_dataid);
                    
                }
                
                
            }
            
            
        }
        
        return CBF_SUCCESS;
        
        
    }
        
        
        
    
    
    /* process a CBF looking for all detector elements
       and process them to produce NXdetector groups in the h5handle.
     
       In addition, create a NXdetector_group from each CBF DIFFRN_DETECTOR
       row, linking the detectors to the detector elements
     
    */
    
    int cbf_require_nxdetectors(const cbf_handle handle,
                                const cbf_h5handle h5handle){
        
        const char * detmodname;
        const char * detname;
        cbf_bookmark bookmark;
        int error=0;
        int processed_nxdetectors=0;
        hid_t instrumentid;
        hid_t detectorid;
        hid_t group_namesid;
        htri_t dsexists;
        unsigned int row, rows, curdet, numdet;
        
        if (!handle || !h5handle) return CBF_ARGUMENT;
        
        /* We will need to use the instrument group or create it*/
        
        cbf_reportnez(cbf_h5handle_require_instrument(h5handle,
                                                      &instrumentid,0),error);
        
        /* First process for DIFFRN_DATA_FRAME (or the deprecated
         DIFFRN_FRAME_DATA) that directly associates data
         with detector elements */
        
        if ((!cbf_find_category(handle,"diffrn_data_frame")||
             !cbf_find_category(handle,"diffrn_frame_data"))
            && !cbf_find_column(handle,"detector_element_id")
            && !cbf_count_rows(handle,&rows)){
            
            
            for (row = 0; row < rows; row++) {
                
                if ((!cbf_find_category(handle,"diffrn_data_frame")||
                     !cbf_find_category(handle,"diffrn_frame_data"))
                    && !cbf_find_column(handle,"detector_element_id")
                    && !cbf_select_row(handle,row)
                    && !cbf_get_value(handle,&detmodname) && detmodname){
                    
                    cbf_reportnez(cbf_h5handle_require_detector(h5handle,NULL,detmodname),error);
                    
                    cbf_reportnez(cbf_set_NX_detector_name(h5handle,detmodname),error);
                    
                }
                
            }
            
            processed_nxdetectors=1;
        }
        
        /* Then process DIFFRN_DETECTOR_ELEMENT */
        
        if (!cbf_find_category(handle,"diffrn_detector_element")
            && !cbf_find_column(handle,"id")
            && !cbf_count_rows(handle,&rows)){
            
             for (row = 0; row < rows; row++) {
                detectorid = CBF_H5FAIL;
                if (!cbf_find_category(handle,"diffrn_detector_element")
                    && !cbf_find_column(handle,"id")
                    && !cbf_select_row(handle,row)
                    && !cbf_get_value(handle,&detmodname) && detmodname) {
                    
                    if (!processed_nxdetectors) {
                        cbf_reportnez(cbf_h5handle_require_detector(h5handle,NULL,detmodname),error);
                        
                        cbf_reportnez(cbf_set_NX_detector_name(h5handle,detmodname),error);
                        
 
                    }
                    
                }
                if (!cbf_find_category(handle,"diffrn_detector_element")
                    &&!cbf_find_column(handle,"detector_id")
                    && !cbf_select_row(handle,row)
                    &&!cbf_get_value(handle,&detname) && detname) {
                    
                    cbf_reportnez(_cbf_NXGrequire(instrumentid,&detectorid,
                                                  detname,
                                                  "NXdetector_group"),error);
                                        
                     /* If there is no group_names dataset, we need to
                     create it, as well as group_index, group_parent
                     and group_type */
                    
                    dsexists = H5Lexists(detectorid,"group_names", H5P_DEFAULT);
                    
                    if (dsexists < 0 || !dsexists ) {
                        
                        cbf_reportnez(cbf_add_h5text_dataset_slab(detectorid,
                                                                  "group_names",
                                                                  detname,
                                                                  (hsize_t) 0L,
                                                                  error),error);
                        cbf_reportnez(cbf_add_h5text_dataset_slab(detectorid,
                                                                  "group_names",
                                                                  detmodname,
                                                                  (hsize_t) 1L,
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_index",
                                                                  1L,
                                                                  (hsize_t) 0L,
                                                                  error),error);
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_index",
                                                                  2L,
                                                                  (hsize_t) 1L,
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_parent",
                                                                  -1L,
                                                                  (hsize_t) 0L,
                                                                  error),error);
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_parent",
                                                                  1L,
                                                                  (hsize_t) 1L,
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_type",
                                                                  1L,
                                                                  (hsize_t) 0L,
                                                                  error),error);
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_type",
                                                                  2L,
                                                                  (hsize_t) 1L,
                                                                  error),error);
                        
                    } else {
                        
                        hid_t datasetspace;
                        
                        int ndims;
                        
                        hsize_t dsdims[1];
                        
                        hsize_t dsmaxdims[1];
                        
                        group_namesid=H5Dopen2(detectorid,"group_names", H5P_DEFAULT);
                        
                        if (group_namesid<0) {
                            
                            if (cbf_H5Ivalid(detectorid)) H5Gclose(detectorid);
                            
                            return CBF_H5ERROR;
                            
                        }

                        datasetspace = H5Dget_space(group_namesid);
                        
                        if (datasetspace < 0) {
                            
                            if (cbf_H5Ivalid(group_namesid)) H5Gclose(group_namesid);
                            
                            if (cbf_H5Ivalid(detectorid)) H5Gclose(detectorid);
                            
                            return CBF_H5ERROR;
                            
                        }
                        
                        cbf_h5reportneg(ndims = H5Sget_simple_extent_ndims(datasetspace),
                                        CBF_H5ERROR,error);
                        
                        if ( error || ndims != 1 ) {
                            
                            if (cbf_H5Ivalid(datasetspace)) H5Sclose(datasetspace);
                            
                            if (cbf_H5Ivalid(group_namesid)) H5Gclose(group_namesid);
                            
                            if (cbf_H5Ivalid(detectorid)) H5Gclose(detectorid);
                            
                            return CBF_H5ERROR;
                            
                        }
                        
                    
                        if (cbf_H5Ivalid(datasetspace)) H5Sclose(datasetspace);
                        
                        if (cbf_H5Ivalid(group_namesid)) H5Gclose(group_namesid);
                        
                        cbf_h5reportneg(H5Sget_simple_extent_dims(datasetspace,
                                                                  dsdims,dsmaxdims),
                                        CBF_H5ERROR,error);
                        
                        cbf_reportnez(cbf_add_h5text_dataset_slab(detectorid,
                                                                  "group_names",
                                                                  detmodname,
                                                                  dsdims[0],
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_index",
                                                                  (long)dsdims[0],
                                                                  dsdims[0],
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_parent",
                                                                  1L,
                                                                  dsdims[0],
                                                                  error),error);
                        
                        cbf_reportnez(cbf_add_h5long_dataset_slab(detectorid,
                                                                  "group_type",
                                                                  2L,
                                                                  dsdims[0],
                                                                  error),error);
                    }
                    
                    if (cbf_H5Ivalid(detectorid)) H5Gclose(detectorid);
                    
                    
                }
                
            }
            
            /* Add in the axes */
            
            cbf_reportnez(cbf_write_h5nxaxes(handle, h5handle),error);
                          
            /* Process the data for each detector module, i.e.
               for each NXdetector group */

            cbf_reportnez(cbf_count_NX_detector_names(h5handle,&numdet),error);
                          
            for (curdet = 0; curdet < numdet; curdet++) {
                
                cbf_reportnez(cbf_get_NX_detector_name(h5handle,curdet,&detmodname),error);
                
                cbf_reportnez(cbf_require_nxdata(handle, h5handle, NULL,
                                                 detmodname, 1),error);
                
            }
            
            return error;
        }
        
        return CBF_NOTFOUND;
        
    }
    
    
	/**
	Check the handle for the presence of an goniometer group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_goniometer
     \sa cbf_h5handle_set_goniometer
     \sa cbf_h5handle_require_goniometer
     \return An error code.
	 */
	int cbf_h5handle_get_goniometer
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxgoniometer)) *group = nx->nxgoniometer;
				else error |= CBF_NOTFOUND;
	}
			/* check for a name */
			if (name) {
				if (nx->nxgoniometer_name) *name = nx->nxgoniometer_name;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}

	/**
     Sets the goniometer group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current goniometer group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_goniometer
     \sa cbf_h5handle_set_goniometer
     \sa cbf_h5handle_require_goniometer
     \return An error code.
	 */
	int cbf_h5handle_set_goniometer
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxgoniometer);
			const char * * const nxName = &(nx->nxgoniometer_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
		return error;
	}

	/**
     This will check if the goniometer group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.

     \param nx The HDF5 handle to use.
	\param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"goniometer"</code>.
     \sa cbf_h5handle_get_goniometer
     \sa cbf_h5handle_set_goniometer
     \sa cbf_h5handle_require_goniometer
     \return An error code.
	 */
	int cbf_h5handle_require_goniometer
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "goniometer";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_instrument(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_goniometer(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXgoniometer"));
				CBF_CALL(cbf_h5handle_set_goniometer(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_goniometer(nx,group,0));
		}
		return error;
	}

	/**
	Check the handle for the presence of an monochromator group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_monochromator
     \sa cbf_h5handle_set_monochromator
     \sa cbf_h5handle_require_monochromator
     \return An error code.
     */
	int cbf_h5handle_get_monochromator
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxmonochromator)) *group = nx->nxmonochromator;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxmonochromator_name) *name = nx->nxmonochromator_name;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}
    
	/**
     Sets the monochromator group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current monochromator group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_monochromator
     \sa cbf_h5handle_set_monochromator
     \sa cbf_h5handle_require_monochromator
     \return An error code.
	 */
	int cbf_h5handle_set_monochromator
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxmonochromator);
			const char * * const nxName = &(nx->nxmonochromator_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
		return error;
	}
    
	/**
     This will check if the monochromator group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.
     
     \param nx The HDF5 handle to use.
     \param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"monochromator"</code>.
     \sa cbf_h5handle_get_monochromator
     \sa cbf_h5handle_set_monochromator
     \sa cbf_h5handle_require_monochromator
     \return An error code.
	 */
	int cbf_h5handle_require_monochromator
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "monochromator";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_instrument(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_monochromator(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
					}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXmonochromator"));
				CBF_CALL(cbf_h5handle_set_monochromator(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_monochromator(nx,group,0));
		}
		return error;
	}

	/**
	Check the handle for the presence of an source group and its name,
	optionally returning any combination of them. The error code
	'CBF_NOTFOUND' will be returned if any of the requested items of data
	cannot be found.

	The handle retains ownership of the returned object and/or string, neither
	of them should be free'd by the caller.

     \param nx A handle to query for the presence of the requested information.
     \param group A place to store the group (if found), or null if the group isn't wanted.
     \param name A place to store the name of the group (if found), or null if the name isn't wanted.
     \sa cbf_h5handle_get_source
     \sa cbf_h5handle_set_source
     \sa cbf_h5handle_require_source
     \return An error code.
	 */
	int cbf_h5handle_get_source
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * * const name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			/* check for a valid group */
			if (group) {
				if (cbf_H5Ivalid(nx->nxsource)) *group = nx->nxsource;
				else error |= CBF_NOTFOUND;
			}
			/* check for a name */
			if (name) {
				if (nx->nxsource_name) *name = nx->nxsource_name;
				else error |= CBF_NOTFOUND;
			}
		}
		return error;
	}
    
	/**
     Sets the source group and name within the handle to the given values.
     Doesn't check or modify the <code>NX_class</code> attribute in any way.
     The handle will take ownership of the group id iff this function succeeds.
     \param nx The handle to add information to.
     \param group The group to be set as the current source group
     \param name The name which the group should be given.
     \sa cbf_h5handle_get_source
     \sa cbf_h5handle_set_source
     \sa cbf_h5handle_require_source
     \return An error code.
	 */
	int cbf_h5handle_set_source
    (const cbf_h5handle nx,
     const hid_t group,
     const char * const name)
	{
			int error = CBF_SUCCESS;
		if (!nx || !cbf_H5Ivalid(group) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			hid_t * const nxGroup = &(nx->nxsource);
			const char * * const nxName = &(nx->nxsource_name);
			const htri_t cmp = cbf_H5Ocmp(*nxGroup,group);
			if (cmp < 0) {
				error |= CBF_H5ERROR;
			} else if (cmp) {
				/* free the old group, take ownership of the new one */
				cbf_H5Gfree(*nxGroup);
				*nxGroup = group;
				/* set the name */
				if (*nxName) free((void*)(*nxName));
				*nxName = _cbf_strdup(name);
			} else {
				/* already set - check that the names match, too */
				if (!*nxName || strcmp(name,*nxName)) error |= CBF_H5DIFFERENT;
			}
		}
			return error;
		}
    
	/**
     This will check if the source group within the handle matches any existing group of the
     same name within the current file. If they don't match a new group is opened or created
     and added to the handle. The <code>NX_class</code> attributes are not checked.
     
     \param nx The HDF5 handle to use.
     \param group An optional pointer to a place where the group should be stored.
     \param name The group name, or null to use the default name of <code>"source"</code>.
     \sa cbf_h5handle_get_source
     \sa cbf_h5handle_set_source
     \sa cbf_h5handle_require_source
     \return An error code.
	 */
	int cbf_h5handle_require_source
    (const cbf_h5handle nx,
     hid_t * const group,
     const char * name)
	{
		int error = CBF_SUCCESS;
		if (!nx) {
			error |= CBF_ARGUMENT;
		} else {
			int match = 0;
			hid_t curr_group = CBF_H5FAIL;
			hid_t parent = CBF_H5FAIL;
			const char * curr_name = NULL;
			const char default_name[] = "source";
			const char * group_name = name ? name : default_name;
			CBF_CALL(cbf_h5handle_get_instrument(nx,&parent,0));
			/* check if the names of the groups match, and if the parent contains the assumed group */
			if (CBF_SUCCESS==cbf_h5handle_get_source(nx,&curr_group,&curr_name)) {
				if (!strcmp(group_name,curr_name)) {
					hid_t test_group = CBF_H5FAIL;
					const int found = cbf_H5Gfind(parent,&test_group,group_name);
					if (CBF_SUCCESS==found) {
						if (!cbf_H5Ocmp(test_group,curr_group)) match = 1;
					} else if (CBF_NOTFOUND!=found) {
						error |= found;
	}
					cbf_H5Gfree(test_group);
				}
			}
			/* if there is no match I need to create/find a suitable group and put it in the handle */
			if (CBF_SUCCESS==error && !match) {
				hid_t new_group = CBF_H5FAIL;
				CBF_CALL(cbf_H5Grequire(parent,&new_group,group_name));
				CBF_CALL(cbf_H5Arequire_string(new_group,"NX_class","NXsource"));
				CBF_CALL(cbf_h5handle_set_source(nx,new_group,group_name));
				if (CBF_SUCCESS!=error) cbf_H5Gfree(new_group);
			}
			/* if there haven't been any major problems, return any requested data */
			CBF_CALL(cbf_h5handle_get_source(nx,group,0));
		}
		return error;
	}
    
    /* Create a dotted CBF location string
     returns a newly allocated string that
     must be freed */

    int cbf_location_string(const char* datablock,
                            const char* category,
                            const char* column,
                            unsigned int row,
                            char * * stringout) {

        size_t dblen, catlen,collen,rowlen;

        char rownum[20];

        if (!stringout) return CBF_ARGUMENT;

        if (!datablock) datablock = "_(NULL)_";
        if (!category) category = "_(NULL)_";
        if (!column) column = "_(NULL)_";

        sprintf(rownum,"%u",row);

        dblen = strlen(datablock);
        catlen = strlen(category);
        collen = strlen(column);
        rowlen = strlen(rownum);

        if (dblen == 0) {
            datablock = "_(NULL)_"; dblen = 8;
        }
        if (catlen == 0) {
            category = "_(NULL)_"; catlen = 8;
        }
        if (collen == 0) {
            column = "_(NULL)_"; collen = 8;
        }

        cbf_failnez(cbf_alloc(((void **) stringout),NULL,
                              1,dblen+catlen+collen+rowlen+4));

        strcpy(*stringout,datablock);

        strcpy((*stringout)+dblen,".");

        strcpy((*stringout)+dblen+1,category);

        strcpy((*stringout)+dblen+1+catlen,".");

        strcpy((*stringout)+dblen+1+catlen+1,column);

        strcpy((*stringout)+dblen+1+catlen+1+collen,".");

        strcpy((*stringout)+dblen+1+catlen+1+collen+1,rownum);

        return CBF_SUCCESS;

    }

    /* Conatenate two strings, returning a newly allocated string */

    int cbf_strcat(const char * string1, const char * string2,
                   char * * stringout) {

        int errorcode;

        size_t len1, len2;

        if (!string1 || !string2 || !stringout) return CBF_ARGUMENT;

        errorcode = 0;

        len1 = strlen(string1);

        len2 = strlen(string2);

        cbf_failnez(cbf_alloc(((void **) stringout),NULL,
                              1,len1+len2+1));

        strcpy(*stringout,string1);

        strcpy((*stringout)+len1,string2);

        return CBF_SUCCESS;

    }


    /* Either open or create a NeXus group*/


    int cbf_require_nxgroup(cbf_h5handle h5handle,
                            const char * nxgroup,
                            const char * nxclass,
                            hid_t parent_id,
                            hid_t * groupid) {

        int errorcode;

        if (!h5handle || !nxgroup || !nxclass || !groupid ) return CBF_ARGUMENT;

        errorcode = 0;

        if (parent_id < 0) parent_id = h5handle->curnxid;

        if (parent_id < 0) parent_id = h5handle->nxid;

        if ((H5Lexists(parent_id,nxgroup,H5P_DEFAULT)) != 1) {

            /* ensure it goes right below the parent_id */

            if (h5handle->curnxid>=0 && h5handle->curnxid!= parent_id) {

                cbf_h5reportneg(H5Gclose(h5handle->curnxid),CBF_ARGUMENT,errorcode);

            }

            h5handle->curnxid = parent_id;

            cbf_reportnez(cbf_H5Gcreate_in_handle(h5handle,nxgroup,groupid),errorcode);

            cbf_reportnez(cbf_apply_h5text_attribute(*groupid,
                                                     "NX_class",nxclass,0),errorcode);

            h5handle->curnxid = CBF_H5FAIL;

        } else {

            if ((*groupid = H5Gopenx(parent_id,nxgroup))<0) return CBF_NOTFOUND;

        }

        return errorcode;

    }

	/* Get an axis' vector and offset.

	Attempts to locate the row of the 'id' column in the given category whose
	value is the same as that given by 'axis_id'. If the row can be found then
	the vector and offset are read.
    
	This reads data directly from the node tree, instead of using a handle.

	\return An error code.
	*/
	int cbf_node_get_axis_vector_and_offset
			(/* The axis category to read axes from. */
			cbf_node * axes,
			/* The (case-sensitive) name of the axis to find and extract data from. */
                                       const char *axis_id,
			/* A place to store the 3-element vector attribute, or 'NULL' if it isn't wanted. */
                                       double vector[3],
			/* A place to store the 3-element offset attribute, or 'NULL' if it isn't wanted. */
			double offset[3])
	{
		int error = CBF_SUCCESS;
		if (!axes || !axis_id) {
			return CBF_ARGUMENT;
		} else if (CBF_CATEGORY != axes->type) {
			error |= CBF_ARGUMENT;
		} else {
			int found = CBF_SUCCESS;
			cbf_node * col = NULL;
			unsigned int row = 0;
			CBF_CALL(cbf_find_child(&col, axes, "id"));
			found = cbf_node_find_nextrow(col, 0, axis_id, &row);
			if (!found) {
        if (vector) {
					cbf_failnez(cbf_find_child(&col,axes,"vector[1]"));
					if (cbf_node_get_doublevalue(col,row,vector+0)) vector[0] = 0.;
					cbf_failnez(cbf_find_child(&col,axes,"vector[2]"));
					if (cbf_node_get_doublevalue(col,row,vector+1)) vector[1] = 0.;
					cbf_failnez(cbf_find_child(&col,axes,"vector[3]"));
					if (cbf_node_get_doublevalue(col,row,vector+2)) vector[2] = 0.;
        }
        if (offset) {
					cbf_failnez(cbf_find_child(&col,axes,"offset[1]"));
					if (cbf_node_get_doublevalue(col,row,offset+0)) offset[0] = 0.;
					cbf_failnez(cbf_find_child(&col,axes,"offset[2]"));
					if (cbf_node_get_doublevalue(col,row,offset+1)) offset[1] = 0.;
					cbf_failnez(cbf_find_child(&col,axes,"offset[3]"));
					if (cbf_node_get_doublevalue(col,row,offset+2)) offset[2] = 0.;
        }
			} else {
				if (CBF_NOTFOUND != found) CBF_PRINT_ERROR(cbf_strerror(found));
				error |= found;
			}
		}
		return error;
	}
        
    /* get an axis vector and offset */

    int cbf_get_axis_vector_and_offset(cbf_handle handle,
                                       const char *axis_id,
                                       double vector[3],
                                       double offset[3]) {

        /***** Allow for missing vector or offset treat as 0 ***/

        if (!handle || !axis_id ) return CBF_ARGUMENT;

        cbf_failnez (cbf_find_category   (handle, "axis"))
        cbf_failnez (cbf_find_column     (handle, "id"))
        cbf_failnez (cbf_find_row        (handle, axis_id))

        if (vector) {

            cbf_failnez (cbf_find_column     (handle, "vector[1]"))
            if (cbf_get_doublevalue (handle, vector)) vector[0] = 0;
            cbf_failnez (cbf_find_column     (handle, "vector[2]"))
            if (cbf_get_doublevalue (handle, vector+1)) vector[1] = 0.;
            cbf_failnez (cbf_find_column     (handle, "vector[3]"))
            if (cbf_get_doublevalue (handle, vector+2)) vector[2] = 0.;

        }

        if (offset) {

            cbf_failnez (cbf_find_column     (handle, "offset[1]"))
            if (cbf_get_doublevalue (handle, offset)) offset[0] = 0.;
            cbf_failnez (cbf_find_column     (handle, "offset[2]"))
            if (cbf_get_doublevalue (handle, offset+1)) offset[1] = 0.;
            cbf_failnez (cbf_find_column     (handle, "offset[3]"))
            if (cbf_get_doublevalue (handle, offset+2)) offset[2] = 0.;

        }

        return CBF_SUCCESS;


    }


    /* Compute the cross-product of 2 3-vectors */

    int cbf_cross_product(double vecin1[3],
                          double vecin2[3],
                          double vecout[3] ) {

        if (!vecin1 || !vecin2 || !vecout) return CBF_ARGUMENT;

        vecout[0] = vecin1[1]*vecin2[2] - vecin1[2]*vecin2[1];

        vecout[1] = vecin1[2]*vecin2[0] - vecin1[0]*vecin2[2];

        vecout[2] = vecin1[0]*vecin2[1] - vecin1[1]*vecin2[0];

        return CBF_SUCCESS;

    }

    /* compute the L2 norm of a 3-vector */

    double cbf_norm(double vector[3]) {

        if (!vector) return -1;

        return sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);

    }

    /* compute the product of a scalar and a vector */

    int cbf_scalar_product(double scalar, double vecin[3], double vecout[3]) {

        if (!vecin || ! vecout) return CBF_ARGUMENT;

        vecout[0] = scalar * vecin[0];

        vecout[1] = scalar * vecin[1];

        vecout[2] = scalar * vecin[2];

        return CBF_SUCCESS;

    }

    /* Apply a matrix to a vector */

    int cbf_apply_matrix(double matrix[3][3], double vecin[3], double vecout[3]) {

        int ii;

        if (!matrix || !vecin || !vecout ) return CBF_ARGUMENT;

        for (ii=0; ii < 3; ii++) {

            vecout[ii] = matrix[ii][0]*vecin[0]
            + matrix[ii][1]*vecin[1]
            + matrix[ii][2]*vecin[2];

            if (fabs(vecout[ii])<=1.e-15) vecout[ii] = 0.;

        }

        return CBF_SUCCESS;

    }

	/* Extract the direction of the beam.

	Attempt to read data from the 'BEAM' axis, if it exists, otherwise attempt
	to read data from the 'SOURCE' axis and multiply the direction by '-1'. If
	neither of those axes can be found then assume that the beam direction is
	[0,0,-1]. The axis names are case-sensitive.

	This reads data directly from the node tree, instead of using a handle.

	\return An error code.
	*/
	static int cbf_node_get_beam_dirn
			(/* The axis category to read axes from. */
			cbf_node * axes,
			/* A place to store the 3-element direction vector. */
			double vector[3])
	{
		int error = CBF_SUCCESS;
		if (!axes || !vector) {
			error |= CBF_ARGUMENT;
		} else if (CBF_CATEGORY != axes->type) {
			error |= CBF_ARGUMENT;
		} else {
			/* take the beam direction, if given, -source if source is given, or [0, 0, -1] */
			if (cbf_node_get_axis_vector_and_offset(axes,"BEAM",vector,NULL)) {
				if (cbf_node_get_axis_vector_and_offset(axes,"SOURCE",vector, NULL)) {
					vector[0] = 0.;
					vector[1] = 0.;
					vector[2] = -1.;
				} else {
					vector[0] = -vector[0];
					vector[1] = -vector[1];
					vector[2] = -vector[2];
				}
			}
		}
		return error;
	}


	/* Extract the direction of gravity.

	Attempt to read data from the 'GRAVITY' axis, if it exists, otherwise
	attempt to read data from the 'UP' axis and multiply the direction by '-1'.
	If neither of those axes can be found then assume that the gravity
	direction is [0,-1,0]. The axis names are case-sensitive.

	This reads data directly from the node tree, instead of using a handle.

	\return An error code.
	*/
	static int cbf_node_get_gravity_dirn
			(/* The axis category to read axes from. */
			cbf_node * axes,
			/* A place to store the 3-element direction vector. */
			double vector[3])
	{
		int error = CBF_SUCCESS;
		if (!axes || !vector) {
			error |= CBF_ARGUMENT;
		} else if (CBF_CATEGORY != axes->type) {
			error |= CBF_ARGUMENT;
		} else {
			/* take gravity if given, -up if up is given, otherwise [0, -1, 0 ] */
			if (cbf_node_get_axis_vector_and_offset(axes,"GRAVITY",vector,NULL)) {
				if (cbf_node_get_axis_vector_and_offset(axes,"UP",vector,NULL)) {
					vector[0] = 0.;
					vector[1] = -1.;
					vector[2] = 0.;
				} else {
					vector[0] = -vector[0];
					vector[1] = -vector[1];
					vector[2] = -vector[2];
				}
			}
		}
		return error;
	}

	/* Get the direction of the beam.

	Locates the 'axis' category in the handle and then forwards to the
	corresponding 'node' variant ('cbf_node_get_beam_dirn') to extract the
	data.

	\return An error code.
	*/
	static int cbf_get_beam_dirn
			(cbf_handle handle,
			 double vector[3])
	{
		int error = CBF_SUCCESS;
		if (!handle) {
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * axes = NULL;
			CBF_CALL(cbf_find_parent(&axes,handle->node,CBF_DATABLOCK));
			CBF_CALL(cbf_find_child(&axes,axes,"axis"));
			CBF_CALL(cbf_node_get_beam_dirn(axes,vector));
		}
		return error;
	}

	/* Get the direction of gravity.

	Locates the 'axis' category in the handle and then forwards to the
	corresponding 'node' variant ('cbf_node_get_gravity_dirn') to extract the
	data.

	\return An error code.
	*/
	static int cbf_get_gravity_dirn
			(cbf_handle handle,
			 double vector[3])
	{
		int error = CBF_SUCCESS;
		if (!handle) {
			error |= CBF_ARGUMENT;
            } else {
			cbf_node * axes = NULL;
			CBF_CALL(cbf_find_parent(&axes,handle->node,CBF_DATABLOCK));
			CBF_CALL(cbf_find_child(&axes,axes,"axis"));
			CBF_CALL(cbf_node_get_gravity_dirn(axes,vector));
            }
		return error;
        }


    /* compute the transform from CBF vectors to NeXus vectors
     Use the transpose to transfrom from NeXus vectors to CBF*/

    int cbf_get_NX_axis_transform(cbf_handle handle,
                                  double matrix [3][3]) {

        double beam[3];

        double gravity[3];

        double x_nx[3], y_nx[3];

        double normx_nx, normy_nx;

        if (!handle || !matrix) return CBF_ARGUMENT;

        /* cross multiple datablocks to find the AXIS category */

        if (cbf_find_tag(handle,"_axis.id")) return CBF_NOTFOUND;

		/* Get the 'beam' and 'gravity' directions, or usable defaults, from the current datablock. */
		cbf_failnez(cbf_get_beam_dirn(handle,beam));
		cbf_failnez(cbf_get_gravity_dirn(handle,gravity));

        cbf_failnez(cbf_cross_product(beam,gravity,x_nx));

        normx_nx = cbf_norm(x_nx);

        if (normx_nx <= 1.e-38) return CBF_ARGUMENT;

        cbf_failnez(cbf_scalar_product(1./normx_nx,x_nx,x_nx));


        cbf_failnez(cbf_cross_product(beam,x_nx,y_nx));

        normy_nx = cbf_norm(y_nx);

        if (normy_nx <= 1.e-38) return CBF_ARGUMENT;

        cbf_failnez(cbf_scalar_product(1./normy_nx,y_nx,y_nx));

        matrix[0][0] = x_nx[0]; matrix[0][1] = x_nx[1]; matrix[0][2] = x_nx[2];

        matrix[1][0] = y_nx[0]; matrix[1][1] = y_nx[1]; matrix[1][2] = y_nx[2];

        matrix[2][0] = beam[0]; matrix[2][1] = beam[1]; matrix[2][2] = beam[2];

        return CBF_SUCCESS;

    }
    
    /* Get a nexus detector name */
    
    int cbf_get_NX_detector_name(cbf_h5handle h5handle,
                                 unsigned int row,
                                 const char * * detector_element) {
    
        if (!h5handle || !detector_element ) return CBF_ARGUMENT;
        
        if (!(h5handle->scratch_tables)
            || cbf_find_datablock(h5handle->scratch_tables,"scratch")
            || cbf_find_category(h5handle->scratch_tables,"scratch_detector")
            || cbf_find_column(h5handle->scratch_tables,"detector_element")
            || cbf_select_row(h5handle->scratch_tables,row)
            || cbf_get_value(h5handle->scratch_tables,detector_element)) {
        
            return CBF_NOTFOUND;
            
        }
        
        return CBF_SUCCESS;
        
    }
    

    
    /* Set a nexus detector name */
    
    int cbf_set_NX_detector_name(cbf_h5handle h5handle, const char * detector_element) {
        
        if (!h5handle || !detector_element ) return CBF_ARGUMENT;
        
        if (!(h5handle->scratch_tables)
            || cbf_require_datablock(h5handle->scratch_tables,"scratch")
            || cbf_require_category(h5handle->scratch_tables,"scratch_detector")
            || cbf_rewind_row(h5handle->scratch_tables)
            || cbf_require_column(h5handle->scratch_tables,"detector_element")) {
            
            return CBF_FORMAT;
            
        }
        
        if (cbf_find_row(h5handle->scratch_tables,detector_element)) {
            
            cbf_failnez(cbf_new_row(h5handle->scratch_tables));
            
            cbf_failnez(cbf_set_value(h5handle->scratch_tables, detector_element));
            
        }
        
        return CBF_SUCCESS;
        
    }
        
    int cbf_count_NX_detector_names(cbf_h5handle h5handle, unsigned int * count) {
        
        if (!h5handle || !count ) return CBF_ARGUMENT;
        
        if (!(h5handle->scratch_tables)
            || cbf_find_datablock(h5handle->scratch_tables,"scratch")
            || cbf_find_category(h5handle->scratch_tables,"scratch_detector")
            || cbf_find_column(h5handle->scratch_tables,"detector_element")
            || cbf_count_rows(h5handle->scratch_tables,count)) {
            
            return CBF_FORMAT;
            
        }

        return CBF_SUCCESS;
        
    }
    
    /* Get the nexus path of an axis, if previously set */
    
    int cbf_get_NX_axis_path(cbf_h5handle h5handle, const char * axis_id, const char * * nexus_path) {
        
        if (!h5handle || !axis_id || !nexus_path ) return CBF_ARGUMENT;
        
        if (!(h5handle->scratch_tables)
                              || cbf_find_datablock(h5handle->scratch_tables,"scratch")
                              || cbf_find_category(h5handle->scratch_tables,"scratch_axis")
            || cbf_find_column(h5handle->scratch_tables,"axis_id")
                              || cbf_rewind_row(h5handle->scratch_tables)
                              || cbf_find_row(h5handle->scratch_tables,axis_id)
                              || cbf_find_column(h5handle->scratch_tables,"nexus_path")
            || cbf_get_value(h5handle->scratch_tables,nexus_path)
            || !(*nexus_path)
            || !cbf_cistrcmp(*nexus_path,".")){
                                  
        
            return CBF_NOTFOUND;
            
        }

        return CBF_SUCCESS;
        
    }


    /* Set the nexus path of an axis */
    
    int cbf_set_NX_axis_path(cbf_h5handle h5handle, const char * axis_id, const char * nexus_path) {
        
        if (!h5handle || !axis_id || !nexus_path ) return CBF_ARGUMENT;
        
        if (!(h5handle->scratch_tables)
            || cbf_require_datablock(h5handle->scratch_tables,"scratch")
            || cbf_require_category(h5handle->scratch_tables,"scratch_axis")
            || cbf_require_column(h5handle->scratch_tables,"axis_id")
            || cbf_rewind_row(h5handle->scratch_tables)) {
            
            return CBF_FORMAT;
            
        }
        
        if (cbf_find_row(h5handle->scratch_tables,axis_id)) {
            
            cbf_failnez(cbf_require_column(h5handle->scratch_tables,"axis_id"));

            cbf_failnez(cbf_new_row(h5handle->scratch_tables));
            
            cbf_failnez(cbf_set_value(h5handle->scratch_tables, axis_id));
            
        }
        
        cbf_failnez(cbf_require_column(h5handle->scratch_tables,"nexus_path"));
        
        cbf_failnez(cbf_set_value(h5handle->scratch_tables,nexus_path));
        
        return CBF_SUCCESS;
        
    }
    
    

    /* Write the HDF5 version of the NeXus axis definitions, if
     the original CBF had axis definitions */

    int cbf_write_h5nxaxes(cbf_handle handle, cbf_h5handle h5handle) {


        int errorcode;
        
        hid_t instrumentid;

        unsigned int rows, row;

        double matrix[3][3];

        hsize_t one=1;

        hsize_t naught=0;

        double zero[1];

        const char* datablock;

        const char * xaxispath;
        

        errorcode = 0;

        zero[0] = 0.;

        /* If we get a transform, there are axes to convert */

        cbf_reportnez(cbf_get_NX_axis_transform(handle, matrix),errorcode);

        if (errorcode) return errorcode;


        /* We will need to use the instrument group or create it*/
        
        cbf_reportnez(cbf_h5handle_require_instrument(h5handle,
                                                      &instrumentid,0),errorcode);
        
        cbf_reportnez(cbf_require_datablock(h5handle->scratch_tables,"scratch"),errorcode);
        
        cbf_reportnez(cbf_require_category(h5handle->scratch_tables,"scratch_axis"),errorcode);
        
        cbf_reportnez(cbf_find_category(handle, "axis"),errorcode);

        cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

        cbf_reportnez(cbf_count_rows(handle,&rows),errorcode);

        cbf_reportnez(cbf_datablock_name(handle,&datablock),errorcode);

        for(row=0; row < rows; row++) {

            char * cbfloc;

            char nxequipment[2048];

            hid_t poiseid = CBF_H5FAIL;
            
			hid_t equipmentid = CBF_H5FAIL;

            hid_t nxaxisid = CBF_H5FAIL;

			hid_t dtype = CBF_H5FAIL, dspace = CBF_H5FAIL, dprop = CBF_H5FAIL;

            const char * equipment;

            const char * equipmentclass;

            const char * equipmentname;
            
            const char * equipmentcomponent;

            const char * axis_id;

            const char * depends_on;

            const char * rotation_axis;

            const char * type;

            const char * system;
            
            const char * axisequipment;
            
            const char * axispath;

            const char * element_id;

            hsize_t scanpoints;

            size_t sscanpoints;
            
            const char * path_axis_general[8];

            const char * path_axis_detector[8];

            const char * path_axis_goniometer[8];

            const char * units;

            double vector[3], offset[3];

            double rotation;
            
            cbf_reportnez(cbf_find_datablock(handle, datablock),errorcode);

            cbf_reportnez(cbf_find_category(handle, "axis"),errorcode);

            cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

            depends_on = ".";

            rotation_axis = ".";
            
            axisequipment = ".";
            
            rotation = 0.0;

            equipment = "general";
            
            equipmentcomponent = ".";

            equipmentclass = "NXtransformations";

            type = "general";

            system = "laboratory";
            
            path_axis_general[0] =
            path_axis_detector[0] =
            path_axis_goniometer[0] = "";
            
            path_axis_general[1] =
            path_axis_detector[1] =
            path_axis_goniometer[1] = (h5handle->nxid_name)?(h5handle->nxid_name):"entry";
            
            path_axis_general[2] =
            path_axis_detector[2] =
            path_axis_goniometer[2] = (h5handle->nxinstrument_name)?(h5handle->nxinstrument_name):"instrument";
            
            path_axis_general[3] = "transformations";
            path_axis_detector[3] = 0;
            path_axis_goniometer[3] = 0;
            
            path_axis_general[4] = 0;

            cbf_reportnez(cbf_select_row(handle,row),errorcode);

            cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

            cbf_reportnez(cbf_get_value(handle,&axis_id),errorcode);
            
            cbf_reportnez(cbf_require_column(h5handle->scratch_tables,"axis_id"),errorcode);
            
            cbf_reportnez(cbf_rewind_row(h5handle->scratch_tables),errorcode);
            
            if (cbf_find_row(h5handle->scratch_tables,axis_id)) {
                
                cbf_reportnez(cbf_new_row(h5handle->scratch_tables),errorcode);
                
                cbf_reportnez(cbf_set_value(h5handle->scratch_tables,axis_id),errorcode);
                
            }

            if (!cbf_find_column(handle,"equipment")) {

                cbf_reportnez(cbf_get_value(handle,&equipment),errorcode);

                if (!equipment)  equipment = "general";

            }

            if (!cbf_find_column(handle,"equipment_component")) {
                
                cbf_reportnez(cbf_get_value(handle,&equipmentcomponent),errorcode);
                
                if (!equipmentcomponent)  equipmentcomponent = ".";
                
            }

            if (!cbf_find_column(handle,"depends_on")) {

                cbf_reportnez(cbf_get_value(handle,&depends_on),errorcode);

                if (!depends_on) depends_on = ".";

            }

            if (!cbf_find_column(handle,"rotation_axis")) {
                
                cbf_reportnez(cbf_get_value(handle,&rotation_axis),errorcode);
                
                if (!rotation_axis) rotation_axis = ".";
                
            }
            

            if (!cbf_find_column(handle,"rotation")) {
                
                cbf_reportnez(cbf_get_doublevalue(handle,&rotation),errorcode);
                
            }


            if (!cbf_find_column(handle,"type")) {

                cbf_reportnez(cbf_get_value(handle,&type),errorcode);

                if (!type) type = "general";

            }

            if (!cbf_find_column(handle,"system")) {

                cbf_reportnez(cbf_get_value(handle,&system),errorcode);

                if (!system||!system[0]) system = "laboratory";

                if (cbf_cistrcmp(system,".")||cbf_cistrcmp(system,"?"))
                    system = "laboratory";

            }

            if (cbf_cistrcmp(system,"laboratory")) {


                cbf_reportnez(cbf_get_axis_vector_and_offset(handle,axis_id,
                                                             vector, offset),errorcode);

            } else {

                double cbfvector[3], cbfoffset[3];
                
                cbf_reportnez(cbf_get_axis_vector_and_offset(handle,axis_id,
                                                             cbfvector, cbfoffset),errorcode);

                system = "McStas_absolute";

                cbf_reportnez(cbf_apply_matrix(matrix,cbfvector,vector),errorcode);

                cbf_reportnez(cbf_apply_matrix(matrix,cbfoffset,offset),errorcode);


            }

            /*  We have the equipment type in equipment and the axis is in axis_id
             If the equipment type is detector, we need to map the axis_id
             to the appropriate detector so we can put this axis in
             /instrument:NXinstrument
               /DETECTORNAME:NXdetector_group
                 /transformations:NXtransformations
                   /AXISID=[]

             If the equipment type is goniometer, we need to map the axis_id
             to the appropriate goniometer, so we can put this axis in
             /instrument:NXinstrument
               /GONIOMETERNAME:NXsample
                 /transformations:NXtransformations
                   /AXISID=[]

             For other equipment types, we put this axis in
             /instrument:NXinstrument
               /transformations:NXtransformations
                 /AXISID=[]
             */

            cbf_reportnez(cbf_get_axis_equipment_id(handle,&equipmentname,equipment,axis_id),errorcode);

            if (!equipment) equipment = "general";

            if (cbf_cistrcmp(equipment,"detector")==0) {

                nxequipment[0]='\0';

                if (equipmentname) {

                    strncat(nxequipment,equipmentname,2020);

                } else {

                    strcpy(nxequipment,"detector");
                }

                equipmentclass = "NXdetector_group";
                
                path_axis_detector[3] = nxequipment;
                
                path_axis_detector[4] = "transformations";
                
                path_axis_detector[5] = axis_id;
                
                path_axis_detector[6] = 0;
                
                axispath = _cbf_strjoin(path_axis_detector,'/');
                
                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  nxequipment, equipmentclass,
                                                  h5handle->nxinst, &equipmentid),errorcode);
                
                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  "transformations", "NXtransformations",
                                                  equipmentid, &poiseid),errorcode);

                
            } else if (cbf_cistrcmp(equipment,"goniometer")==0) {

                nxequipment[0]='\0';

                if (equipmentname) {

                    strncat(nxequipment,equipmentname,2020);

                    nxequipment[2047] = 0;

                } else {

                    strcpy(nxequipment,"sample");
                }

                equipmentclass = "NXsample";
                
                path_axis_goniometer[3] = nxequipment;
                
                path_axis_goniometer[4] = "transformations";
                
                path_axis_goniometer[5] = axis_id;
                
                path_axis_goniometer[6] = 0;
                
                axispath = _cbf_strjoin(path_axis_goniometer,'/');
                
                cbf_reportnez(cbf_h5handle_require_sample(h5handle,0,nxequipment),errorcode);
                
                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  nxequipment, equipmentclass,
                                                  h5handle->nxinst, &equipmentid),errorcode);

                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  "transformations", "NXtransformations",
                                                  equipmentid, &poiseid),errorcode);

                

            } else if (cbf_cistrcmp(equipment,"general")==0
                       || cbf_cistrcmp(equipment,"beam")==0
                       || cbf_cistrcmp(equipment,"gravity")==0){

                strcpy(nxequipment,"transformations");

                equipmentclass = "NXtransformations";
                
                path_axis_general[4] = axis_id;
                
                path_axis_general[5] = 0;
                
                axispath = _cbf_strjoin(path_axis_general,'/');

                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  "transformations", "NXtransformations",
                                                  h5handle->nxinst, &poiseid),errorcode);

            } else {
                
                if (!cbf_cistrcmp(equipmentcomponent,".")) {
                    
                    equipmentcomponent = equipment;
                    
                    equipment = "general";
                
                }
                
                strcpy(nxequipment,"transformations");
                
                equipmentclass = "NXtransformations";
                
                path_axis_general[4] = axis_id;
                
                path_axis_general[5] = 0;
                
                axispath = _cbf_strjoin(path_axis_general,'/');

                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  "transformations", "NXtransformations",
                                                  h5handle->nxinst, &poiseid),errorcode);


            }

            if (axispath) {
            
                if (cbf_get_NX_axis_path(h5handle, axis_id, &xaxispath)) {
            
                    cbf_reportnez(cbf_set_NX_axis_path(h5handle, axis_id, axispath),errorcode);

                    cbf_debug_print3("logged axis_id '%s' axis_path '%s'\n", axis_id, axispath);
            
                    free((void*)axispath);
                
                    cbf_reportnez(cbf_get_NX_axis_path(h5handle, axis_id, &axispath),errorcode);
                
            } else {
                
                    axispath = xaxispath;
                
                }
                
            }
            

           
            cbf_reportnez(cbf_get_axis_parameters(handle,
                                                  &sscanpoints,
                                                  &units,
                                                  equipment,
                                                  axis_id),errorcode);

            scanpoints = (hsize_t)sscanpoints;

            /* At this point we are ready to write the field AXISID[] */



            {
                
                if (scanpoints > 0) {

                    hsize_t scanpointsfound;

					hid_t mtype = CBF_H5FAIL;
                    
                    hsize_t chunk[] = {1};
                    
                    hsize_t maxsize[] = {H5S_UNLIMITED};

                    size_t sscanpointsfound;

                    double * scanarray;

                    cbf_reportnez(cbf_alloc(((void **) &scanarray),NULL,
                                            sizeof(double),scanpoints),errorcode);

                    cbf_reportnez(cbf_get_axis_scan_points(handle,
                                                           scanarray,
                                                           (size_t)scanpoints,
                                                           &sscanpointsfound,
                                                           units,
                                                           axis_id),errorcode);

                    scanpointsfound = (hsize_t)sscanpointsfound;

                    if (sscanpointsfound==0) scanpointsfound=1;

                    cbf_h5reportneg(dspace = H5Screate_simple(1,&scanpointsfound,maxsize),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(dtype = H5Tcopy(H5T_IEEE_F64LE),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(mtype = H5Tcopy(H5T_NATIVE_DOUBLE),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(dprop = H5Pcreate(H5P_DATASET_CREATE),CBF_ALLOC,errorcode);
                    
                    cbf_h5reportneg(H5Pset_chunk(dprop,1,chunk),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(nxaxisid = H5Dcreatex(poiseid,axis_id,dtype,dspace,dprop),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Dwrite(nxaxisid, mtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)scanarray),CBF_ALLOC,errorcode);

                    if (!errorcode) {
                        
                        cbf_debug_print3("write axis %s data %d points\n",axis_id,(int)scanpointsfound);
                    }
                    
                    cbf_reportnez(cbf_free((void **)(&scanarray),NULL),errorcode);

                    cbf_h5reportneg(H5Sclose(dspace),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Tclose(dtype),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Tclose(mtype),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Pclose(dprop),CBF_ALLOC,errorcode);

                    if (units) {

                        errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                                "units",units,errorcode);
                    }
                } else {

                    hid_t mtype;

                    hsize_t chunk[] = {1};

                    hsize_t maxsize[] = {H5S_UNLIMITED};
                    
                    cbf_h5reportneg(dspace = H5Screate_simple(1,&naught,maxsize),CBF_ALLOC,errorcode);
                    
                    cbf_h5reportneg(dtype = H5Tcopy(H5T_IEEE_F64LE),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(mtype = H5Tcopy(H5T_NATIVE_DOUBLE),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(dprop = H5Pcreate(H5P_DATASET_CREATE),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Pset_chunk(dprop,1,chunk),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(nxaxisid = H5Dcreatex(poiseid,axis_id,dtype,dspace,dprop),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Dwrite(nxaxisid, mtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)zero),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Sclose(dspace),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Tclose(dtype),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Tclose(mtype),CBF_ALLOC,errorcode);

                    cbf_h5reportneg(H5Pclose(dprop),CBF_ALLOC,errorcode);


                }

                errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                        "transformation_type",
                                                        type,
                                                        errorcode);
                
                if (cbf_cistrcmp(system,"McStas_absolute")) {
                    
                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                        "system",system,errorcode);
                    
                }

                if (cbf_norm(offset) > 1.e-20) {
                    
                    errorcode |= cbf_apply_h5vector_attribute(nxaxisid,
                                                              "offset",(double *)offset,3,errorcode);
                    
                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                            "offset_units","mm",errorcode);
                    
                }
                
                    errorcode |= cbf_apply_h5vector_attribute(nxaxisid,
                                                          "vector",(double *)vector,3,errorcode);

                if (!cbf_cistrcmp(depends_on,".")) {

                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                            "depends_on",depends_on,errorcode);
                } else {
 
                    const char * dopath = NULL;
                    
                    const char * doequip;
                    
                    const char * doequipname;
                    
                    if (cbf_get_NX_axis_path(h5handle,depends_on,&dopath)){
                        
                    cbf_reportnez(cbf_get_axis_equipment(handle,depends_on,&doequip),errorcode);
                    
                    cbf_reportnez(cbf_get_axis_equipment_id(handle,&doequipname,doequip,depends_on),errorcode);
                    
                    if (!cbf_cistrcmp(doequip,"detector")) {
                        
                        path_axis_detector[3] = doequipname;
                        
                        path_axis_detector[4] = "transformations";
                        
                        path_axis_detector[5] = depends_on;
                        
                        path_axis_detector[6] = 0;
                        
                        dopath = _cbf_strjoin(path_axis_detector,'/');

                        
                    } else if (!cbf_cistrcmp(doequip,"goniometer")) {
                        
                        path_axis_goniometer[3] = doequipname;
                        
                        path_axis_goniometer[4] = "transformations";
                        
                        path_axis_goniometer[5] = depends_on;
                        
                        path_axis_goniometer[6] = 0;
                        
                        dopath = _cbf_strjoin(path_axis_goniometer,'/');
                        
                    } else {
                        
                        path_axis_general[4] = depends_on;
                        
                        path_axis_general[5] = 0;
                        
                        dopath = _cbf_strjoin(path_axis_general,'/');
                    }
                    
                        cbf_reportnez(cbf_set_NX_axis_path(h5handle,depends_on,dopath),errorcode);
                        
                        errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                                "depends_on",
                                                                dopath,errorcode);
                        
                        cbf_debug_print3("logged axis_id '%s' axis path '%s'\n", depends_on, dopath);

                        free((void*)dopath);
                        
                        cbf_reportnez(cbf_get_NX_axis_path(h5handle,depends_on,&dopath),errorcode);
                        
                    } else {
                        
                    if (dopath) {
                        
                        errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                                "depends_on",
                                                                dopath,errorcode);
                    }
                    }

                }

                if (cbf_cistrcmp(rotation_axis,".")) {
                    
                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                            "rotation_axis",rotation_axis,errorcode);
                    
                    errorcode |= cbf_apply_h5vector_attribute(nxaxisid,
                                                            "rotation",&rotation,1,errorcode);
                    
                }
                
                if (equipment && cbf_cistrcmp(equipment,".")) {
                    
                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                            "equipment",equipment,errorcode);                    
                }

                if (equipmentcomponent && cbf_cistrcmp(equipmentcomponent,".")) {
                    
                    errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                            "equipment_component",equipmentcomponent,errorcode);
                }

                cbf_reportnez(cbf_location_string(datablock,"axis","vector",row,&cbfloc),errorcode);

                errorcode |= cbf_apply_h5text_attribute(nxaxisid,
                                                        "cbf_location",
                                                        cbfloc,
                                                        errorcode);

                if (!cbf_cistrcmp(equipment,"detector") &&
                    !cbf_get_axis_element_id(handle,&element_id,
                                             equipmentname,equipment,axis_id)) {
                        
                        htri_t linked;
                        
                        hid_t this_detector = CBF_H5FAIL;
                        
                        errorcode |= cbf_h5handle_require_detector(h5handle,&this_detector,element_id);
                        
                        linked = H5Lexists(this_detector, axis_id, H5P_DEFAULT);
                        
                        if (linked == 0) {
                            
                            cbf_h5reportneg(H5Olink(nxaxisid,this_detector,
                                                    axis_id,H5P_DEFAULT,H5P_DEFAULT), CBF_FORMAT, errorcode);
                            
                        }
                        
                        
                    }
                
                cbf_h5reportneg(H5Dclose(nxaxisid),CBF_FORMAT,errorcode);

                cbf_reportnez(cbf_free((void **)&cbfloc,NULL),errorcode);
                
                
            }

            cbf_h5reportneg(H5Gclose(poiseid),CBF_FORMAT,errorcode);
            
            if (cbf_H5Ivalid(equipmentid)) {
                
                cbf_h5reportneg(H5Gclose(equipmentid),CBF_FORMAT,errorcode);
                
                
            }

        }

        return errorcode;

    }

    /* apply a double vector attribute to a group or dataset */

    int cbf_apply_h5vector_attribute(hid_t hid,
                                     const char* attribname,
                                     const double* attribvec,
                                     const size_t dimension,
                                     int errorcode)
    {

        hid_t attribspace, attribtype, attribid;

        hid_t attribmemtype;

        hsize_t dims[1];

        attribspace = attribtype = attribmemtype = attribid = CBF_H5FAIL;

        /* ensure arguments all given */

        if (hid < 0 || !attribname|| !attribvec || dimension < 1 ) return CBF_ARGUMENT;

        cbf_h5reportneg(attribspace = H5Screate(H5S_SIMPLE),CBF_ALLOC,errorcode);

        dims[0] = dimension;

        cbf_h5reportneg(H5Sset_extent_simple(attribspace, 1, dims, NULL),CBF_FORMAT,errorcode);

        cbf_h5reportneg(attribtype = H5Tcopy(H5T_IEEE_F64LE),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribmemtype = H5Tcopy(H5T_NATIVE_DOUBLE),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                              attribtype,
                                              attribspace,
                                              H5P_DEFAULT),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Awrite(attribid,attribmemtype,
                                 attribvec),CBF_ALLOC,errorcode);

        if (attribspace >= 0)  H5Sclose(attribspace);

        if (attribtype >= 0)   H5Tclose(attribtype);

        if (attribmemtype >= 0)   H5Tclose(attribmemtype);

        if (attribid >= 0)     H5Aclose(attribid);

        return errorcode;

    }


    /* apply a long attribute to a group or dataset */

    int cbf_apply_h5longasstr_attribute(hid_t hid,
                                        const char* attribname,
                                        const long attriblong,
                                        int errorcode)
    {
        char buffer[20];

        if (attriblong > -10 && attriblong < 10) {

            sprintf(buffer,"%ld",attriblong);

        } else {

            sprintf(buffer,"0x%lx",attriblong);

        }

        return cbf_apply_h5text_attribute(hid,attribname,buffer,errorcode);

    }


    /* apply an integer attribute to a group or dataset as a string */

    int cbf_apply_h5intasstr_attribute(hid_t hid,
                                       const char* attribname,
                                       const int attribint,
                                       int errorcode)
    {
        char buffer[20];

        if (attribint > -10 && attribint < 10) {

            sprintf(buffer,"%d",attribint);

        } else {

            sprintf(buffer,"0x%x",attribint);

        }

        return cbf_apply_h5text_attribute(hid,attribname,buffer,errorcode);

    }


    /* apply a reference attribute to a group or dataset */

    int cbf_apply_h5reference_attribute(hid_t hid,
                                      const char* attribname,
                                      const hobj_ref_t attribref,
                                      int errorcode)
    {
        hid_t attribspace, attribtype, attribid;
        
        attribspace = attribtype = attribid = CBF_H5FAIL;
        
        /* ensure arguments all given */
        
        if (hid < 0 || !attribname ) return CBF_ARGUMENT;
        
        cbf_h5reportneg(attribspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(attribtype = H5Tcopy(H5T_STD_REF_OBJ),CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                              attribtype,
                                              attribspace,
                                              H5P_DEFAULT),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(H5Awrite(attribid,attribtype,
                                 &attribref),CBF_ALLOC,errorcode);
        
        if (attribspace >= 0)  H5Sclose(attribspace);
        
        if (attribtype >= 0)   H5Tclose(attribtype);
        
        if (attribid >= 0)     H5Aclose(attribid);
        
        return errorcode;
        
    }




    /* apply a integer attribute to a group or dataset */

    int cbf_apply_h5integer_attribute(hid_t hid,
                                      const char* attribname,
                                      const int attribint,
                                      int errorcode)
    {

        hid_t attribspace, attribtype, attribid;

        attribspace = attribtype = attribid = CBF_H5FAIL;

        /* ensure arguments all given */

        if (hid < 0 || !attribname ) return CBF_ARGUMENT;

        cbf_h5reportneg(attribspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribtype = H5Tcopy(H5T_NATIVE_INT),CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(attribtype,1),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                              attribtype,
                                              attribspace,
                                              H5P_DEFAULT),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Awrite(attribid,attribtype,
                                 &attribint),CBF_ALLOC,errorcode);

        if (attribspace >= 0)  H5Sclose(attribspace);

        if (attribtype >= 0)   H5Tclose(attribtype);

        if (attribid >= 0)     H5Aclose(attribid);

        return errorcode;

    }


    /* apply a text attribute to a group or dataset */

    int cbf_apply_h5text_attribute(hid_t hid,
                                   const char* attribname,
                                   const char* attribtext,
                                   int errorcode)
    {

        hid_t attribspace, attribtype, attribid;

        htri_t attribexists;

        attribspace = attribtype = attribid = CBF_H5FAIL;

        /* ensure arguments all given */

        if (hid < 0 || !attribname || !attribtext ) return CBF_ARGUMENT;

        if (!cbf_cistrcmp(attribname,"depends_on")) {
            cbf_debug_print2("cbf_apply_h5text_attribute('depends_on','%s')\n",attribtext);
        }


        /* if the attribute exists, check the value is the same */

        attribexists = H5Aexists(hid,attribname);

        if (attribexists > 0) {

            hsize_t attribsize = 0;

            hsize_t memtype = 0;

            char * attribtextbuffer;

            cbf_h5reportneg(attribid = H5Aopen(hid, attribname, H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(attribtype = H5Aget_type(attribid),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(attribsize = H5Tget_size(attribtype),CBF_H5ERROR,errorcode);

            cbf_reportnez(cbf_alloc(((void **) &attribtextbuffer),NULL,
                                    1,attribsize+1),errorcode);

            cbf_h5reportneg(memtype = H5Tget_native_type(attribtype,H5T_DIR_ASCEND),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(H5Aread(attribid,memtype,&attribtextbuffer),CBF_H5ERROR,errorcode);

            if (cbf_cistrcmp(attribtext,attribtextbuffer)) errorcode |= CBF_H5DIFFERENT;

            if (cbf_H5Ivalid(memtype)) H5Tclose(memtype);

            if (cbf_H5Ivalid(attribtype)) H5Tclose(attribtype);

            if (cbf_H5Ivalid(attribid)) H5Aclose(attribid);

            if (attribtextbuffer) cbf_reportnez(cbf_free((void * *) &attribtextbuffer,NULL),errorcode);

            return errorcode;

        }

        cbf_h5reportneg(attribspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(attribtype,strlen(attribtext)),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                              attribtype,
                                              attribspace,
                                              H5P_DEFAULT),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Awrite(attribid,attribtype,
                                 (const void *)attribtext),CBF_ALLOC,errorcode);

        if (attribspace >= 0)  H5Sclose(attribspace);

        if (attribtype >= 0)   H5Tclose(attribtype);

        if (attribid >= 0)     H5Aclose(attribid);

        return errorcode;

    }

    /* apply a text attribute slab to a dataset
     
       Actually works with a text data set and makes
       the attribute be an object reference to that
       dataset.  The name of the dataset is the
       name of the attribute with the optional
       prefix and suffix
     
     */

    int cbf_add_h5text_attribute_slab(hid_t datasetid,
                                    hid_t groupid,
                                    const char* attributename,
                                    const char* attributetext,
                                    const char* datasetnameprefix,
                                    const char* datasetnamesuffix,
                                    const hsize_t slab,
                                    int errorcode) {
        
        const char * datasetname;
        
        const char * datasetnameparts[4];
        
        int iparts;
        
        int error;
        
        hobj_ref_t dsref;
        
        htri_t aexists;
        
        
        error = 0;
        
        if (!cbf_H5Ivalid(datasetid)
            || !cbf_H5Ivalid(groupid)
            || !attributename
            || !attributetext) return CBF_ARGUMENT;
        
        iparts = 0;
        
        if (datasetnameprefix) datasetnameparts[iparts++] = datasetnameprefix;
        
        datasetnameparts[iparts++] = attributename;
        
        if (datasetnamesuffix) datasetnameparts[iparts++] = datasetnamesuffix;
        
        datasetnameparts[iparts++] = 0;
    
        datasetname = _cbf_strjoin(datasetnameparts,'_');
        
        error |= cbf_add_h5text_dataset_slab(groupid,datasetname,attributetext,slab,0);
        
        cbf_h5reportneg(H5Rcreate(&dsref,groupid,datasetname,H5R_OBJECT,-1),CBF_H5ERROR,error);
        
        aexists = H5Aexists(datasetid,attributename);
        
        if (aexists < 0 || !aexists ) {

            error |= cbf_apply_h5reference_attribute(datasetid,attributename,dsref,error);
        

        }
        
        free((void*)datasetname);
        
        return CBF_SUCCESS;
        
        
     }

    /* apply a text dataset slab to a group

     places the specified datasettext in the specified slab of the
     specified datasetname for group hid.  The dataset is created
     if it does not already exist.

     The slabs are indexed from 0

     */

    int cbf_add_h5text_dataset_slab(hid_t hid,
                                      const char* datasetname,
                                      const char* datasettext,
                                      const hsize_t slab,
                                      int errorcode)
    {
        hid_t datasetspace, datasettype, datasetid;

        hid_t memspace, memtype;

        hid_t ndatasettype;

        hid_t ndatasetspace;

        hid_t nmemtype;

        int ndims;

        hsize_t offset[1] = {0};

        hsize_t stride[1] = {1};

        hsize_t count[1]  = {1};

        hsize_t chunk[1] = {1};

        hsize_t curdim[1];

        hsize_t memsize[1] = {1};

        htri_t dsexists;

        hsize_t dssize[1];

        hsize_t maxdssize[1];

        hsize_t dsdims[1];

        hsize_t dsmaxdims[1];

        hsize_t dsslab;

        hid_t anondataset;

        void * datasettextbuffer;

        size_t old_size, new_size;

        datasetspace = datasettype = memspace = memtype = CBF_H5FAIL;

        ndatasetspace = ndatasettype = nmemtype = CBF_H5FAIL;

        datasetid = CBF_H5FAIL;

        memsize[0] = 1;

        dssize[0] = 1;

        maxdssize[0] = H5S_UNLIMITED;

        chunk[0] = 1;


        /* ensure arguments all given */

        if (hid < 0 || !datasetname ||
            !datasettext || errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname, H5P_DEFAULT);

        if (dsexists < 0 ||
            !dsexists
            || (datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT))< 0) {

            /* Create the dataset if we were unable to open it */

            cbf_h5reportneg(datasettype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Tset_size(datasettype,strlen(datasettext)),CBF_ALLOC,errorcode);

            cbf_reportnez(cbf_H5Dcreate(hid,&datasetid,datasetname,1,dssize,maxdssize,chunk,datasettype),errorcode);

            curdim[0] = 0;

            dsdims[0] = 0;

        }

        if (datasetid <= 0) {

            datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT);

        }

        cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(ndims = H5Sget_simple_extent_ndims(datasetspace),CBF_FORMAT,errorcode);

        if ( errorcode || ndims != 1 ) return CBF_FORMAT;

        old_size = H5Tget_size(datasettype);

        new_size = strlen(datasettext);

        cbf_h5reportneg(H5Sget_simple_extent_dims(datasetspace,
                                                  dsdims,dsmaxdims),CBF_FORMAT,errorcode);

        if ( old_size < new_size ) {

            ndatasettype = CBF_H5FAIL;

            cbf_h5reportneg(ndatasettype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

            /* rebuild the dataset with longer strings */

            if (old_size+((old_size+1)>>1)>= new_size) {

                new_size = old_size+((old_size+1)>>1);

            }

            cbf_reportnez(cbf_alloc(&datasettextbuffer,NULL,
                                    1,new_size+1),errorcode);

            if (datasettype >= 0) H5Tclose(datasettype);

            datasettype = ndatasettype;

            cbf_h5reportneg(H5Tset_size(datasettype,new_size),CBF_ALLOC,errorcode);

            cbf_h5reportneg(memtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

            cbf_h5reportneg(nmemtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

            cbf_h5reportneg(memspace = H5Screate_simple(1,memsize,NULL),CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Tset_size(memtype,new_size),CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Tset_size(nmemtype,new_size),CBF_ALLOC,errorcode);

            cbf_reportnez(cbf_H5Dcreate(hid,&anondataset,NULL,1,dsdims,maxdssize,chunk,datasettype),errorcode);

            for (dsslab=0; dsslab < dsdims[0]; dsslab++) {

                offset[0] = dsslab;

                cbf_h5reportneg(H5Sselect_hyperslab(datasetspace,H5S_SELECT_SET,
                                                    offset,stride,count,0), CBF_FORMAT,errorcode);

                if (H5Dread(datasetid, memtype, memspace, datasetspace,
                            H5P_DEFAULT, (void *)datasettextbuffer)>=0) {

                    curdim[0] = dsslab+1;

                    cbf_h5reportneg(H5Dset_extent(anondataset,curdim),CBF_FORMAT,errorcode);

                    offset[0] = dsslab;

                    stride[0] = 1;

                    count[0] = 1;

                    cbf_reportnez(cbf_H5Dwrite2(anondataset,offset,stride,count,(void *)datasettextbuffer,memtype),errorcode);

                }

            }

            if (nmemtype >= 0) H5Tclose(nmemtype);

            if (ndatasetspace >= 0) H5Sclose(ndatasetspace);

            if (datasetspace >= 0) H5Sclose(datasetspace);

            cbf_h5reportneg(H5Ldelete(hid,datasetname,H5P_DEFAULT), CBF_FORMAT, errorcode);

            cbf_h5reportneg(H5Olink(anondataset,hid,datasetname,H5P_DEFAULT,H5P_DEFAULT), CBF_FORMAT, errorcode);

            if (datasetid >= 0) H5Dclose(datasetid);

            datasetid = anondataset;

            if (datasettextbuffer) cbf_free(&datasettextbuffer,NULL);

            if (memtype >= 0) H5Tclose(memtype);

            datasetspace = memtype = CBF_H5FAIL;

        }

        if (datasetspace >=0 )H5Sclose(datasetspace);

        datasetspace = CBF_H5FAIL;


        if (slab == H5S_UNLIMITED) {

            offset[0] = dsdims[0];

            curdim[0] = dsdims[0]+1;

        } else {

            offset[0] = slab;

            curdim[0] = slab+1;

        }

        cbf_h5reportneg(H5Dset_extent(datasetid,curdim),CBF_FORMAT,errorcode);

        stride[0] = 1;

        count[0] = 1;

        cbf_reportnez(cbf_H5Dwrite2(datasetid,offset,stride,count,(void *)datasettext,datasettype),errorcode);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        if (memtype >= 0)       H5Tclose(memtype);

        return errorcode;

    }

    /* apply a text dataset to a group */

    int cbf_add_h5text_dataset(hid_t hid,
                                 const char* datasetname,
                                 const char* datasettext,
                                 int errorcode)
    {

		hid_t datasetspace = CBF_H5FAIL, datasettype = CBF_H5FAIL, datasetid = CBF_H5FAIL, datasetprop = CBF_H5FAIL;

        htri_t dsexists;

        /* ensure arguments all given */

        if (hid < 0 || !datasetname || !datasettext
            || errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname,H5P_DEFAULT);

        if ( dsexists >=0 && dsexists ) {

            hsize_t dssize;

			hid_t memtype = CBF_H5FAIL;

            int datasetrank = -1;

            char * datasettextbuffer = NULL;

            /* The dataset exists, and will be replaced with an array
             of strings, unless it is already an array, in which case
             we just add to it */

            cbf_h5reportneg(datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_FORMAT,errorcode);

            cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_FORMAT,errorcode);

            cbf_h5reportneg(datasetrank = H5Sget_simple_extent_ndims(datasetspace),CBF_FORMAT,errorcode);

            if (datasetrank == 1) {

                /* This is an array, write the next slab */

                if (datasetspace >= 0)  H5Sclose(datasetspace);

                if (datasettype >= 0)   H5Tclose(datasettype);

                if (datasetid >= 0)     H5Dclose(datasetid);

                cbf_reportnez(cbf_add_h5text_dataset_slab(hid,
                                              datasetname,
                                              datasettext,
                                              H5S_UNLIMITED, errorcode),errorcode);


                return errorcode;

            }

            dssize = H5Tget_size(datasettype);

            cbf_reportnez(cbf_alloc((void * *)(&datasettextbuffer),NULL,
                                    1,dssize+1),errorcode);

            cbf_h5reportneg(memtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Tset_size(memtype,dssize),CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Dread(datasetid, memtype, H5S_ALL, datasetspace,
                                    H5P_DEFAULT, (void *)datasettextbuffer),CBF_FORMAT,errorcode);

            /* unlink the current dataset and write the old data and the new data */

            cbf_h5reportneg(H5Ldelete(hid,datasetname,H5P_DEFAULT),CBF_FORMAT,errorcode);

            cbf_reportnez(cbf_add_h5text_dataset_slab(hid,
                                                        datasetname,
                                                        datasettextbuffer,
                                                        0, errorcode),errorcode);

            cbf_reportnez(cbf_add_h5text_dataset_slab(hid,
                                                        datasetname,
                                                        datasettext,
                                                        1, errorcode),errorcode);

            if (datasettextbuffer) cbf_free((void * *)(&datasettextbuffer),NULL);

            if (datasetspace >= 0)  H5Sclose(datasetspace);

            if (datasettype >= 0)   H5Tclose(datasettype);

            if (memtype >= 0)       H5Tclose(memtype);

            if (datasetid >= 0)     H5Dclose(datasetid);


            return errorcode;

        }

        cbf_h5reportneg(datasetspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasettype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(datasettype,strlen(datasettext)),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetid = H5Dcreatex(hid,datasetname,
                                               datasettype,
                                               datasetspace,
                                               datasetprop),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Dwrite(datasetid,datasettype,
                                 H5S_ALL,H5S_ALL,
                                 H5P_DEFAULT,
                                 (const void *)datasettext),
                        CBF_ALLOC,errorcode);

        if (datasetprop >= 0)   H5Pclose(datasetprop);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        return errorcode;

    }


    /* apply a text attribute to a group or dataset */

    int cbf_apply_h5text_dataset(hid_t hid,
                                   const char* attribname,
                                   const char* attribtext,
                                   int errorcode)
    {

        hid_t attribspace, attribtype, attribid;

        attribspace = attribtype = attribid = CBF_H5FAIL;

        /* ensure arguments all given */

        if (hid < 0 || !attribname || !attribtext ) return CBF_ARGUMENT;

        cbf_h5reportneg(attribspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(attribtype,strlen(attribtext)),CBF_ALLOC,errorcode);

        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                              attribtype,
                                              attribspace,
                                              H5P_DEFAULT),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Awrite(attribid,attribtype,
                                 (const void *)attribtext),CBF_ALLOC,errorcode);

        if (attribspace >= 0)  H5Sclose(attribspace);

        if (attribtype >= 0)   H5Tclose(attribtype);

        if (attribid >= 0)     H5Aclose(attribid);

        return errorcode;

    }

    /* apply a double dataset slab to a group

     places the specified datasetvalue in the specified slab of the
     specified datasetname for group hid.  The dataset is created
     if it does not already exist.

     The slabs are indexed from 0

     */

    int cbf_add_h5double_dataset_slab(hid_t hid,
                                    const char* datasetname,
                                    const double datasetvalue,
                                    const hsize_t slab,
                                    int errorcode)
    {
        hid_t datasetspace, datasettype, datasetid;

        hid_t memspace, memtype;

        hid_t ndatasettype;

        hid_t ndatasetspace;

        hid_t nmemtype;

        int ndims;

        hsize_t offset[1] = {0};

        hsize_t stride[1] = {1};

        hsize_t count[1]  = {1};

        hsize_t chunk[1] = {1};

        hsize_t curdim[1];

        hsize_t memsize[1] = {1};

        htri_t dsexists;

        hsize_t dssize[1];

        hsize_t maxdssize[1];

        hsize_t dsdims[1];

        hsize_t dsmaxdims[1];

        datasetspace = datasettype = memspace = memtype = CBF_H5FAIL;

        ndatasetspace = ndatasettype = nmemtype = CBF_H5FAIL;

        datasetid = CBF_H5FAIL;

        memsize[0] = 1;

        dssize[0] = 1;

        maxdssize[0] = H5S_UNLIMITED;

        chunk[0] = 1;

        /* ensure arguments all given */

        if (hid < 0 || !datasetname ||
            errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname, H5P_DEFAULT);

        if ( dsexists < 0 ||
            !dsexists
            || (datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT))< 0 ) {

            /* Create the dataset if we were unable to open it */

            cbf_h5reportneg(datasettype = H5Tcopy(H5T_IEEE_F64LE),CBF_ALLOC,errorcode);

            cbf_reportnez(cbf_H5Dcreate(hid,&datasetid,datasetname,1,dssize,maxdssize,chunk,datasettype),errorcode);

            curdim[0] = 0;

            dsdims[0] = 0;

        } 

        if ( datasetid <= 0 ) {

            datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT);

        }

        cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(ndims = H5Sget_simple_extent_ndims(datasetspace),CBF_FORMAT,errorcode);

        if ( errorcode || ndims != 1 ) return CBF_FORMAT;

        cbf_h5reportneg(H5Sget_simple_extent_dims(datasetspace,
                                                  dsdims,dsmaxdims),CBF_FORMAT,errorcode);

        if (datasetspace >=0 )H5Sclose(datasetspace);

        datasetspace = CBF_H5FAIL;


        if (slab == H5S_UNLIMITED) {

            offset[0] = dsdims[0];

            curdim[0] = dsdims[0]+1;

        } else {

            offset[0] = slab;

            curdim[0] = slab+1;

        }

        cbf_h5reportneg(H5Dset_extent(datasetid,curdim),CBF_FORMAT,errorcode);

        stride[0] = 1;

        count[0] = 1;

        cbf_reportnez(cbf_H5Dwrite(datasetid,offset,stride,count,(void *)(&datasetvalue)),errorcode);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        if (memtype >= 0)       H5Tclose(memtype);

        return errorcode;

    }

    /* apply a text dataset to a group */

    int cbf_add_h5double_dataset(hid_t hid,
                               const char* datasetname,
                               const double datasetvalue,
                               int errorcode)
    {

		hid_t datasetspace = CBF_H5FAIL, datasettype = CBF_H5FAIL, datasetid = CBF_H5FAIL, datasetprop = CBF_H5FAIL;

        htri_t dsexists;

        double dsvalue;

        /* ensure arguments all given */

        if (hid < 0 || !datasetname
            || errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname,H5P_DEFAULT);

        if ( dsexists >=0 && dsexists ) {

			hid_t memtype = CBF_H5FAIL;

            int datasetrank = -1;

            /* The dataset exists, and will be replaced with an array
             of strings, unless it is already an array, in which case
             we just add to it */

            cbf_h5reportneg(datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasetrank = H5Sget_simple_extent_ndims(datasetspace),CBF_H5ERROR,errorcode);

            if (datasetrank == 1) {

                /* This is an array, write the next slab */

                if (datasetspace >= 0)  H5Sclose(datasetspace);

                if (datasettype >= 0)   H5Tclose(datasettype);

                if (datasetid >= 0)     H5Dclose(datasetid);

                cbf_reportnez(cbf_add_h5double_dataset_slab(hid,
                                                          datasetname,
                                                          datasetvalue,
                                                          H5S_UNLIMITED, errorcode),errorcode);


                return errorcode;

            }

            cbf_h5reportneg(memtype=H5Tget_native_type(datasettype,H5T_DIR_ASCEND),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(H5Dread(datasetid, memtype, H5S_ALL, datasetspace,
                                    H5P_DEFAULT, (void *)(&dsvalue)),CBF_H5ERROR,errorcode);

            /* unlink the current dataset and write the old data and the new data */

            cbf_h5reportneg(H5Ldelete(hid,datasetname,H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_reportnez(cbf_add_h5double_dataset_slab(hid,
                                                      datasetname,
                                                      dsvalue,
                                                      0, errorcode),errorcode);

            cbf_reportnez(cbf_add_h5double_dataset_slab(hid,
                                                      datasetname,
                                                      datasetvalue,
                                                      1, errorcode),errorcode);

            if (datasetspace >= 0)  H5Sclose(datasetspace);

            if (datasettype >= 0)   H5Tclose(datasettype);

            if (memtype >= 0)       H5Tclose(memtype);

            if (datasetid >= 0)     H5Dclose(datasetid);


            return errorcode;

        }

        cbf_h5reportneg(datasetspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasettype = H5Tcopy(H5T_IEEE_F64LE),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetid = H5Dcreatex(hid,datasetname,
                                               datasettype,
                                               datasetspace,
                                               datasetprop),
                        CBF_ALLOC,errorcode);

        dsvalue = datasetvalue;

        cbf_h5reportneg(H5Dwrite(datasetid,datasettype,
                                 H5S_ALL,H5S_ALL,
                                 H5P_DEFAULT,
                                 (const void *)(&dsvalue)),
                        CBF_ALLOC,errorcode);

        if (datasetprop >= 0)   H5Pclose(datasetprop);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        return errorcode;

    }

    /* apply a long dataset slab to a group

     places the specified datasetvalue in the specified slab of the
     specified datasetname for group hid.  The dataset is created
     if it does not already exist.

     The slabs are indexed from 0

     */

    int cbf_add_h5long_dataset_slab(hid_t hid,
                                      const char* datasetname,
                                      const long datasetvalue,
                                      const hsize_t slab,
                                      int errorcode)
    {
        hid_t datasetspace, datasettype, datasetid;

        hid_t memspace, memtype;

        hid_t ndatasettype;

        hid_t ndatasetspace;

        hid_t nmemtype;

        int ndims;

        hsize_t offset[1] = {0};

        hsize_t stride[1] = {1};

        hsize_t count[1]  = {1};

        hsize_t chunk[1] = {1};

        hsize_t curdim[1];

        hsize_t memsize[1] = {1};

        htri_t dsexists;

        hsize_t dssize[1];

        hsize_t maxdssize[1];

        hsize_t dsdims[1];

        hsize_t dsmaxdims[1];

        datasetspace = datasettype = memspace = memtype = CBF_H5FAIL;

        ndatasetspace = ndatasettype = nmemtype = CBF_H5FAIL;

        datasetid = CBF_H5FAIL;

        memsize[0] = 1;

        dssize[0] = 1;

        maxdssize[0] = H5S_UNLIMITED;

        chunk[0] = 1;

        /* ensure arguments all given */

        if (hid < 0 || !datasetname ||
             errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname, H5P_DEFAULT);

        if ( dsexists < 0 ||
            !dsexists
            || (datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT))< 0 ) {

            /* Create the dataset if we were unable to open it */

            cbf_h5reportneg(datasettype = H5Tcopy(H5T_STD_I64LE),CBF_ALLOC,errorcode);

            cbf_reportnez(cbf_H5Dcreate(hid,&datasetid,datasetname,1,dssize,maxdssize,chunk,datasettype),errorcode);

            curdim[0] = 0;

            dsdims[0] = 0;

        } 

        if ( datasetid <= 0 ) {

            datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT);

        }

        cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_FORMAT,errorcode);

        cbf_h5reportneg(ndims = H5Sget_simple_extent_ndims(datasetspace),CBF_FORMAT,errorcode);

        if ( errorcode || ndims != 1 ) return CBF_FORMAT;

        cbf_h5reportneg(H5Sget_simple_extent_dims(datasetspace,
                                                  dsdims,dsmaxdims),CBF_FORMAT,errorcode);

        if (datasetspace >=0 )H5Sclose(datasetspace);

        datasetspace = CBF_H5FAIL;


        if (slab == H5S_UNLIMITED) {

            offset[0] = dsdims[0];

            curdim[0] = dsdims[0]+1;

        } else {

            offset[0] = slab;

            curdim[0] = slab+1;

        }

        cbf_h5reportneg(H5Dset_extent(datasetid,curdim),CBF_FORMAT,errorcode);

        stride[0] = 1;

        count[0] = 1;

        cbf_reportnez(cbf_H5Dwrite(datasetid,offset,stride,count,(void *)(&datasetvalue)),errorcode);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        if (memtype >= 0)       H5Tclose(memtype);

        return errorcode;

    }

    /* apply a long dataset to a group */

    int cbf_add_h5long_dataset(hid_t hid,
                                 const char* datasetname,
                                 const long datasetvalue,
                                 int errorcode)
    {

		hid_t datasetspace = CBF_H5FAIL, datasettype = CBF_H5FAIL, datasetid = CBF_H5FAIL, datasetprop = CBF_H5FAIL;

        htri_t dsexists;

        long dsvalue;

        /* ensure arguments all given */

        if (hid < 0 || !datasetname 
            || errorcode) return CBF_ARGUMENT;

        dsexists = H5Lexists(hid,datasetname,H5P_DEFAULT);

        if ( dsexists >=0 && dsexists ) {

			hid_t memtype = CBF_H5FAIL;

            int datasetrank = -1;

            /* The dataset exists, and will be replaced with an array
             of strings, unless it is already an array, in which case
             we just add to it */

            cbf_h5reportneg(datasetid = H5Dopen2(hid,datasetname, H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasettype = H5Dget_type(datasetid),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasetspace = H5Dget_space(datasetid),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(datasetrank = H5Sget_simple_extent_ndims(datasetspace),CBF_H5ERROR,errorcode);

            if (datasetrank == 1) {

                /* This is an array, write the next slab */

                if (datasetspace >= 0)  H5Sclose(datasetspace);

                if (datasettype >= 0)   H5Tclose(datasettype);

                if (datasetid >= 0)     H5Dclose(datasetid);

                cbf_reportnez(cbf_add_h5long_dataset_slab(hid,
                                                          datasetname,
                                                          datasetvalue,
                                                          H5S_UNLIMITED, errorcode),errorcode);


                return errorcode;

            }

            cbf_h5reportneg(memtype=H5Tget_native_type(datasettype,H5T_DIR_ASCEND),CBF_H5ERROR,errorcode);

            cbf_h5reportneg(H5Dread(datasetid, memtype, H5S_ALL, datasetspace,
                                    H5P_DEFAULT, (void *)(&dsvalue)),CBF_H5ERROR,errorcode);

            /* unlink the current dataset and write the old data and the new data */

            cbf_h5reportneg(H5Ldelete(hid,datasetname,H5P_DEFAULT),CBF_H5ERROR,errorcode);

            cbf_reportnez(cbf_add_h5double_dataset_slab(hid,
                                                        datasetname,
                                                        dsvalue,
                                                        0, errorcode),errorcode);

            cbf_reportnez(cbf_add_h5double_dataset_slab(hid,
                                                        datasetname,
                                                        datasetvalue,
                                                        1, errorcode),errorcode);

            if (datasetspace >= 0)  H5Sclose(datasetspace);

            if (datasettype >= 0)   H5Tclose(datasettype);

            if (memtype >= 0)       H5Tclose(memtype);

            if (datasetid >= 0)     H5Dclose(datasetid);


            return errorcode;

        }

        cbf_h5reportneg(datasetspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasettype = H5Tcopy(H5T_STD_I64LE),CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(datasetid = H5Dcreatex(hid,datasetname,
                                               datasettype,
                                               datasetspace,
                                               datasetprop),
                        CBF_ALLOC,errorcode);

        dsvalue = datasetvalue;

        cbf_h5reportneg(H5Dwrite(datasetid,datasettype,
                                 H5S_ALL,H5S_ALL,
                                 H5P_DEFAULT,
                                 (const void *)(&dsvalue)),
                        CBF_ALLOC,errorcode);

        if (datasetprop >= 0)   H5Pclose(datasetprop);

        if (datasetspace >= 0)  H5Sclose(datasetspace);

        if (datasettype >= 0)   H5Tclose(datasettype);

        if (datasetid >= 0)     H5Dclose(datasetid);

        return errorcode;

    }




    /* Write a binary value to an HDF5 file */

    int cbf_write_h5binary (cbf_handle handle,
                            cbf_node *column,
                            unsigned int row,
                            cbf_h5handle h5handle)
    {
		hid_t valid = CBF_H5FAIL, valtype = CBF_H5FAIL, memtype = CBF_H5FAIL, valprop = CBF_H5FAIL, valspace = CBF_H5FAIL;

        int errorcode;

        char rownum[10];

        cbf_file *infile;

        char digest [25];

        long start;

        size_t size;

        hsize_t hsize[3];

        unsigned int compression;

        unsigned char * rawdata;

        void * uncompressedarray;

        int id, bits, sign, type, checked_digest, realarray;

        const char *byteorder;

        size_t dimover, dimfast, dimmid, dimslow;

        size_t padding;

        size_t elsize;

        size_t nelems_read;

        unsigned int cd_values[CBF_H5Z_FILTER_CBF_NELMTS];

        /* Check the arguments */

        if (!handle || !h5handle || !h5handle->hfile)

            return CBF_ARGUMENT;

        if (!cbf_is_binary (column, row))

            return CBF_ARGUMENT;

        if (cbf_is_mimebinary (column, row))

            return CBF_ARGUMENT;

        cbf_failnez (cbf_get_bintext (column, row, &type, &id, &infile,
                                      &start, &size, &checked_digest,
                                      digest, &bits, &sign, &realarray,
                                      &byteorder, &dimover, &dimfast, &dimmid, &dimslow,
                                      &padding, &compression))

        if (dimslow == 0) dimslow = 1;

        if (dimmid == 0) dimmid = 1;

        if (dimfast == 0) dimfast = 1;

        /* Position the file at the start of the binary section */

        cbf_failnez (cbf_set_fileposition (infile, start, SEEK_SET))

        /* Calculate the digest if necessary */

        if (!cbf_is_base64digest (digest))
        {

            /* Compute the message digest */

            cbf_failnez (cbf_md5digest (infile, size, digest))


            /* Go back to the start of the binary data */

            cbf_failnez (cbf_set_fileposition (infile, start, SEEK_SET))


            /* Update the entry */

            checked_digest = 1;

            cbf_failnez (cbf_set_bintext (column, row, type,
                                          id, infile, start, size,
                                          checked_digest, digest, bits,
                                          sign,  realarray,
                                          byteorder, dimover, dimfast, dimmid, dimslow,
                                          padding, compression))
        }

        /* Discard any bits in the buffers */


        infile->bits [0] = 0;
        infile->bits [1] = 0;

        valid = valtype = valprop = valspace = CBF_H5FAIL;

        sprintf(rownum,"%d", row);

        /* prepare the errorcode */

        errorcode = 0;

        if (h5handle->flags & CBF_H5_OPAQUE) {

            /* Treat the image as an opaque stream of size bytes */

            hsize[0] = size;

            cbf_h5reportneg(valspace = H5Screate_simple(1,hsize,NULL),
                            CBF_ALLOC,errorcode);

            cbf_h5reportneg(valtype = H5Tcreate(H5T_OPAQUE,1),
                            CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Tset_tag(valtype,"stream of opaque bytes"),
                            CBF_ALLOC,errorcode);


            cbf_h5reportneg(valprop = H5Pcreate(H5P_DATASET_CREATE),
                            CBF_ALLOC,errorcode);

            cbf_h5reportneg(valid = H5Dcreatex(h5handle->colid,rownum,
                                               valtype,valspace,
                                               valprop),
                            CBF_ALLOC,errorcode);


            /* get all the data */

            /* first ensure enough space at infile->characters
             for size characters, which means we need enough
             at characters->base for size + the old data,
             if any */

            cbf_reportnez(cbf_set_io_buffersize(infile, size),errorcode);

            /* now we can safely do the read

             because of the file positioning done, infile->characters
             is actually the same as infile_characters_base for a
             file stream based file */

            rawdata = (unsigned char*) infile->characters;

            if (infile->characters_used < size) {


                /* We cannot get any more characters from
                 a temporary file of file without a stream */

                if (infile->temporary || !infile->stream)  {

                    errorcode |= CBF_FILEREAD;

                }

                if (!errorcode && fread(rawdata, 1,
                                        size-(infile->characters_used), infile->stream)
                    != size-infile->characters_used)
                    errorcode |= CBF_FILEREAD;

                if (!errorcode) infile->characters_used = size;

            }

            cbf_h5reportneg(H5Dwrite(valid,valtype,
                                     valspace,H5S_ALL,H5P_DEFAULT,rawdata),
                            CBF_ARGUMENT,errorcode);

        } else {

            /* Treat the data as an array to be compressed

             chunking in planes dimfast x dimmid

             */

            hsize_t chunk[3];

            hsize_t maxdim[3];

            hsize[0] = dimslow;

            chunk[0] = 1;

            maxdim[0] = H5S_UNLIMITED;

            hsize[1] = chunk[1] = maxdim[1] = dimmid;

            hsize[2] = chunk[2] = maxdim[2] = dimfast;

            cbf_h5reportneg(valspace = H5Screate_simple(3,hsize,maxdim),
                            CBF_ALLOC,errorcode);

            if (realarray) {

                if (byteorder[0]=='l' || byteorder[0]=='L') {

                    if (bits <= 32) {

                        cbf_h5reportneg(valtype = H5Tcopy(H5T_IEEE_F32LE),
                                        CBF_ALLOC,errorcode);
                        cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_FLOAT),
                                        CBF_ALLOC,errorcode)


                    } else {

                        cbf_h5reportneg(valtype = H5Tcopy(H5T_IEEE_F64LE),
                                        CBF_ALLOC,errorcode)
                        cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_DOUBLE),
                                        CBF_ALLOC,errorcode)


                    }


                } else {

                    if (bits <= 32) {

                        cbf_h5reportneg(valtype = H5Tcopy(H5T_IEEE_F32BE),
                                        CBF_ALLOC,errorcode);
                        cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_FLOAT),
                                        CBF_ALLOC,errorcode)

                    } else {

                        cbf_h5reportneg(valtype = H5Tcopy(H5T_IEEE_F64BE),
                                        CBF_ALLOC,errorcode)
                        cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_DOUBLE),
                                        CBF_ALLOC,errorcode)

                    }

                }


            } else {

                if (byteorder[0]=='l' || byteorder[0]=='L') {

                    if (bits <= 8) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I8LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_CHAR),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U8LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_UCHAR),
                                            CBF_ALLOC,errorcode);
                        }

                    } else if (bits <= 16) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I16LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_SHORT),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U16LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_USHORT),
                                            CBF_ALLOC,errorcode);
                        }

                    } else if (bits <= 32) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I32LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_INT),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U32LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_UINT),
                                            CBF_ALLOC,errorcode);
                        }

                    } else {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I64LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_LLONG),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U64LE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_ULLONG),
                                            CBF_ALLOC,errorcode);
                        }

                    }


                } else {

                    if (bits <= 8) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I8BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_CHAR),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U8BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_UCHAR),
                                            CBF_ALLOC,errorcode);
                        }

                    } else if (bits <= 16) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I16BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_SHORT),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U16BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_USHORT),
                                            CBF_ALLOC,errorcode);
                        }

                    } else if (bits <= 32) {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I32BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_INT),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U32BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_UINT),
                                            CBF_ALLOC,errorcode);

                        }

                    } else {

                        if (sign) {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_I64BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_LLONG),
                                            CBF_ALLOC,errorcode);

                        } else {

                            cbf_h5reportneg(valtype = H5Tcopy(H5T_STD_U64BE),
                                            CBF_ALLOC,errorcode);
                            cbf_h5reportneg(memtype = H5Tcopy(H5T_NATIVE_ULLONG),
                                            CBF_ALLOC,errorcode);

                        }

                    }

                }

            }


            cbf_h5reportneg(valprop = H5Pcreate(H5P_DATASET_CREATE),
                            CBF_ALLOC,errorcode);

            cbf_h5reportneg(H5Pset_chunk(valprop,3,chunk),
                            CBF_ALLOC,errorcode);

            cd_values[CBF_H5Z_FILTER_CBF_COMPRESSION] = compression;
            cd_values[CBF_H5Z_FILTER_CBF_RESERVED]    = 0;
            cd_values[CBF_H5Z_FILTER_CBF_BINARY_ID]   = id;
            cd_values[CBF_H5Z_FILTER_CBF_PADDING]     = padding;
            cd_values[CBF_H5Z_FILTER_CBF_ELSIZE]      = (bits+7)/8;
            cd_values[CBF_H5Z_FILTER_CBF_ELSIGN]      = sign;
            cd_values[CBF_H5Z_FILTER_CBF_REAL]        = realarray;
            cd_values[CBF_H5Z_FILTER_CBF_DIMFAST]     = dimfast;
            cd_values[CBF_H5Z_FILTER_CBF_DIMMID]      = dimmid;
            cd_values[CBF_H5Z_FILTER_CBF_DIMSLOW]     = dimslow;

            if (h5handle->flags & CBF_H5_REGISTER_COMPRESSIONS) {

                if (!H5Zfilter_avail(CBF_H5Z_FILTER_CBF)) {

                    cbf_h5reportneg(H5Zregister(CBF_H5Z_CBF),CBF_ALLOC,errorcode);

                }
            }

            cbf_h5reportneg(H5Pset_filter(valprop,CBF_H5Z_FILTER_CBF,
                                          H5Z_FLAG_OPTIONAL,
                                          CBF_H5Z_FILTER_CBF_NELMTS,
                                          cd_values),CBF_ALLOC,errorcode);

            /* cbf_debug_pring2("errorcode on setting filter CBF_H5Z_FILTER_CBF %d\n",errorcode); */

            valid = H5Dcreatex(h5handle->colid,rownum,
                               valtype,valspace,
                               valprop);


            /* get all the data */

            elsize = (bits+7)/8;

            cbf_reportnez(cbf_alloc(((void **) &uncompressedarray),NULL,
                                    elsize,dimover),errorcode);

            nelems_read = 0;

            /* Get the data */

            {
                int text_realarray, text_id;

                size_t text_dimover, text_dimfast, text_dimmid, text_dimslow, text_padding;

                const char *text_byteorder;

                cbf_reportnez (cbf_get_binary (column, row,
                                               &text_id,
                                               uncompressedarray,
                                               elsize,
                                               sign,
                                               dimover,
                                               &nelems_read,
                                               &text_realarray,
                                               &text_byteorder,
                                               &text_dimover,
                                               &text_dimfast,
                                               &text_dimmid,
                                               &text_dimslow,
                                               &text_padding),errorcode);
            }

            if (nelems_read < dimover) {

                cbf_failnez(cbf_free(&uncompressedarray,NULL));

                return errorcode|CBF_ENDOFDATA;

            }

            cbf_h5reportneg(H5Dwrite(valid,memtype,H5S_ALL,
                                     H5S_ALL,H5P_DEFAULT,uncompressedarray),
                            CBF_ARGUMENT,errorcode);

            if (memtype >= 0) {

                cbf_h5failneg(H5Tclose(memtype),CBF_ARGUMENT);

            }

            cbf_failnez(cbf_free(&uncompressedarray,NULL));


        }

        errorcode |= cbf_apply_h5integer_attribute(valid,"signal",row+1,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"compression",compression,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"binid",id,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"bits",bits,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"sign",sign,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"bintype",type,errorcode);
        errorcode |= cbf_apply_h5text_attribute(valid,"cbftype","bnry",errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"checked_digest",checked_digest,errorcode);
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"size",(long)size,errorcode);
        errorcode |= cbf_apply_h5intasstr_attribute(valid,"real",realarray,errorcode);
        errorcode |= cbf_apply_h5text_attribute(valid,"byteorder",byteorder,errorcode);
        if (cbf_is_base64digest (digest)) {
            errorcode |= cbf_apply_h5text_attribute(valid,"MD5_digest",digest,errorcode);
        }
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"dimover",(long)dimover,errorcode);
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"dimfast",(long)dimfast,errorcode);
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"dimmid",(long)dimmid,errorcode);
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"dimslow",(long)dimslow,errorcode);
        errorcode |= cbf_apply_h5longasstr_attribute(valid,"padding",(long)padding,errorcode);


        /* now link the data to entry:NXentry/data:NXdata */

        if (h5handle->dataid<0){

            /* ensure it goes right below NXentry */

            if (h5handle->curnxid>=0) {

                cbf_h5reportneg(H5Gclose(h5handle->curnxid),CBF_ARGUMENT,errorcode);

                h5handle->curnxid = CBF_H5FAIL;

            }

            cbf_reportnez(cbf_H5Gcreate_in_handle(h5handle,"data",&(h5handle->dataid)),errorcode);

            cbf_failnez(cbf_apply_h5text_attribute(h5handle->dataid,
                                                   "NX_class","NXdata",0));

        }

        {
            char target_path[1024];

            char full_name[1024];

            size_t len;

            const char * pstr;

            strcpy(target_path,"/entry/CBF_cbf/");

            full_name[0] = '\0';

            len = strlen(target_path)+strlen(rownum)+1;

            pstr = (h5handle->bookmark).datablock?
            (h5handle->bookmark).datablock:"_(null)_";

            if (len+strlen(pstr)>1020) return CBF_FORMAT;

            strncat(target_path,pstr,1020-len);

            strcat(target_path,"/");

            strncat(full_name,pstr,1020-len);

            strcat(full_name,".");

            len = strlen(target_path)+strlen(rownum)+1;

            pstr = (h5handle->bookmark).category?
            (h5handle->bookmark).category:"_(null)_";

            if (len+strlen(pstr)>1021) return CBF_FORMAT;

            strncat(target_path,pstr,1021-len);

            strcat(target_path,"/");

            strncat(full_name,pstr,1020-len);

            strcat(full_name,".");

            len = strlen(target_path)+strlen(rownum)+1;

            pstr = (h5handle->bookmark).column?
            (h5handle->bookmark).column:"_(null)_";

            if (len+strlen(pstr)>1022) return CBF_FORMAT;

            strncat(target_path,pstr,1022-len);

            strcat(target_path,"/");

            strncat(full_name,pstr,1020-len);

            strcat(full_name,".");

            len = strlen(target_path);

            if (len+strlen(rownum)>1023) return CBF_FORMAT;

            strncat(target_path,rownum,1023-len);

            strncat(full_name,rownum,1023-len);

            errorcode |= cbf_apply_h5text_attribute(valid,"target",
                                                    target_path,errorcode);


            cbf_h5reportneg(H5Lcreate_hard(h5handle->colid,rownum,
                                           h5handle->dataid,full_name,H5P_DEFAULT,H5P_DEFAULT),
                            CBF_ARGUMENT,
                            errorcode);

        }

        if (valid >= 0) {

            cbf_h5failneg(H5Dclose(valid),CBF_ARGUMENT);

        }

        if (valspace >= 0) {

            cbf_h5failneg(H5Sclose(valspace),CBF_ARGUMENT);

        }

        if (valtype >= 0) {

            cbf_h5failneg(H5Tclose(valtype),CBF_ARGUMENT);

        }

        if (valprop >= 0) {

            cbf_h5failneg(H5Pclose(valprop),CBF_ARGUMENT);

        }

        return errorcode;



    }

    /* Write an ascii value to an HDF5 file */

    int cbf_write_h5ascii (cbf_handle handle,
                           unsigned int row,
                           const char *string,
                           cbf_h5handle h5handle)
    {
        static const char missing [] = { CBF_TOKEN_NULL, '?', '\0' };


        hid_t valid, valtype, valprop, valspace;

        char rownum[10];

        char* typecode;

        int errorcode;

        /* Check the arguments */

        if (!handle || !h5handle || h5handle->hfile < 0) return CBF_ARGUMENT;

        valid = valtype = valprop = valspace = CBF_H5FAIL;

        sprintf(rownum,"%d", row);

        if (!string)

            string = missing;

        else

            if (*string != CBF_TOKEN_WORD       &&
                *string != CBF_TOKEN_SQSTRING   &&
                *string != CBF_TOKEN_DQSTRING   &&
                *string != CBF_TOKEN_SCSTRING   &&
                *string != CBF_TOKEN_TSQSTRING  &&
                *string != CBF_TOKEN_TDQSTRING  &&
                *string != CBF_TOKEN_BKTSTRING  &&
                *string != CBF_TOKEN_BRCSTRING  &&
                *string != CBF_TOKEN_PRNSTRING  &&
                *string != CBF_TOKEN_NULL)

                return CBF_ARGUMENT;

        /* prepare the errorcode */

        errorcode = 0;

        /* Create a scalar dataspace */

        cbf_h5reportneg(valspace = H5Screate(H5S_SCALAR),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(valtype = H5Tcopy(H5T_C_S1),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(valtype,strlen(string+1)),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(valprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(valid = H5Dcreatex(h5handle->colid,rownum,
                                           valtype,valspace,valprop),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Dwrite(valid,valtype,
                                 H5S_ALL,H5S_ALL,H5P_DEFAULT,string+1),
                        CBF_ARGUMENT,errorcode);

        errorcode |= cbf_get_value_type(string,(const char **)&typecode);

        errorcode |= cbf_apply_h5text_attribute(valid,
                                                "cbftype",typecode,errorcode);

        if (valid >= 0) {

            cbf_h5failneg(H5Dclose(valid),CBF_ARGUMENT);

        }

        if (valspace >= 0) {

            cbf_h5failneg(H5Sclose(valspace),CBF_ARGUMENT);

        }

        if (valtype >= 0) {

            cbf_h5failneg(H5Tclose(valtype),CBF_ARGUMENT);

        }

        if (valprop >= 0) {

            cbf_h5failneg(H5Pclose(valprop),CBF_ARGUMENT);

        }

        return errorcode;


    }

    /* Write a value to an HDF5 file */

    int cbf_write_h5value (cbf_handle handle, cbf_node *column, unsigned int row,
                           cbf_h5handle h5handle)
    {
        const char *text;

        /* Check the arguments */

        if (!column || !h5handle || h5handle->hfile < 0)

            return CBF_ARGUMENT;

        if (row >= column->children)

            return CBF_NOTFOUND;


        /* Get the value */

        cbf_failnez (cbf_get_columnrow (&text, column, row))


        /* Missing value? */

        if (!text)

            return cbf_write_h5ascii (handle, row, text, h5handle);


        /* Plain ASCII? */

        cbf_failnez (cbf_value_type ((char *) text))

        if (*text == CBF_TOKEN_WORD     ||
            *text == CBF_TOKEN_SQSTRING ||
            *text == CBF_TOKEN_DQSTRING ||
            *text == CBF_TOKEN_SCSTRING ||
            *text == CBF_TOKEN_TSQSTRING ||
            *text == CBF_TOKEN_TDQSTRING ||
            *text == CBF_TOKEN_PRNSTRING ||
            *text == CBF_TOKEN_BKTSTRING ||
            *text == CBF_TOKEN_BRCSTRING ||
            *text == CBF_TOKEN_NULL)

            return cbf_write_h5ascii (handle, row, text, h5handle);


        /* Plain binary? */

        if (*text == CBF_TOKEN_BIN || *text == CBF_TOKEN_TMP_BIN)

            return cbf_write_h5binary (handle, column, row, h5handle);


        /* Undecoded MIME? */

        if (*text == CBF_TOKEN_MIME_BIN)
        {
            /* Convert the value to a normal binary section */

            cbf_failnez (cbf_mime_temp (column, row))

            return cbf_write_h5binary (handle, column, row, h5handle);
        }


        /* Fail */

        return CBF_ARGUMENT;
    }

	/* Write a CBF value into a NeXus file
     Will add a piece of data with a given name to /entry/group@groupNXclass/subGroup@subGroupNXclass/name */

	int cbf_map_h5value(
                        const char * const name, const char * const value,
                        const char * const group, const char * const groupNXclass,
                        const char * const subGroup, const char * const subGroupNXclass,
                        const size_t attrc, const cbf_name_value_pair * const attrv,
                        cbf_h5handle h5handle)
	{
		/* check args & define local variables */
		int error = (attrc != 0 && !attrv) ? CBF_ARGUMENT : CBF_SUCCESS;
		hid_t h5group = CBF_H5FAIL, h5subGroup = CBF_H5FAIL, h5dataset = CBF_H5FAIL, h5type = CBF_H5FAIL;
		const cbf_name_value_pair * attrit = attrv;

		/* Get the datatype */
		cbf_reportnez(cbf_H5Tcreate_string(&h5type, strlen(value)), error);

		/* Assume nxid is a valid handle, need to ensure that the /entry/instrument group exists, then ensure the detector group exists */
		cbf_reportnez(cbf_require_nxgroup(h5handle, group, groupNXclass, h5handle->nxid, &h5group), error);
		cbf_reportnez(cbf_require_nxgroup(h5handle, subGroup, subGroupNXclass, h5group, &h5subGroup), error);

		/* write some data */
		cbf_reportnez(cbf_H5Dcreate(h5subGroup,&h5dataset,name,0,0,0,0,h5type),error);
		cbf_reportnez(cbf_H5Dwrite(h5dataset,0,0,0,value),error);
		for (; attrit < attrv+attrc; ++attrit)
			cbf_reportnez(cbf_H5Arequire_string(h5dataset,attrit->name,attrit->value),error);

		/*  clean up */
		if (cbf_H5Ivalid(h5type)) cbf_H5Tfree(h5type);
		if (cbf_H5Ivalid(h5dataset)) cbf_H5Dfree(h5dataset);
		if (cbf_H5Ivalid(h5subGroup)) cbf_H5Gfree(h5subGroup);
		if (cbf_H5Ivalid(h5group)) cbf_H5Gfree(h5group);
		return error;
	}

    /* Write a category to an HDF5 file */

    int cbf_write_h5category (cbf_handle handle,
                              const cbf_node *category,
                              cbf_h5handle h5handle)
    {
		unsigned int column, row;

		const char instGroup[] = "instrument";

		const char instGroupClass[] = "NXinstrument";

        hid_t instrumentid;

        unsigned int colrow;

        cbf_fast_bookmark fbkmk;

        int errorcode;

        errorcode = 0;

        /* Check the arguments */

        if (!category || !h5handle || h5handle->rootid <0 || h5handle->dbid < 0)

            return CBF_ARGUMENT;

        /* bookmark the handle */

        cbf_failnez(cbf_get_fast_bookmark(handle,&fbkmk));


        /* If another category is open, close it */


        if (h5handle->colid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);

            h5handle->colid = CBF_H5FAIL;

        }

        if (h5handle->catid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);

            h5handle->catid = CBF_H5FAIL;

        }

        /* save the category name in the read bookmark */

        (h5handle->bookmark).category = category->name;

        /* Write the name under the open save frame or datablock */

        if (h5handle->sfid <0) {

            cbf_h5failneg(h5handle->catid=H5Gcreatex(h5handle->dbid,
                                                     (category->name)?(category->name):"_(null)_"),
                          CBF_FORMAT);


        } else {
            cbf_h5failneg(h5handle->catid=H5Gcreatex(h5handle->dbid,
                                                     (category->name)?(category->name):"_(null)_"),
                          CBF_FORMAT);
        }

		cbf_debug_print(category->name);

        handle->node = (cbf_node *)category;

        handle->row = 0;

		
        /* Process diffrn_detector category */

        if (!cbf_cistrcmp(category->name,"diffrn_detector"))
		{
            unsigned int maxrows;
            unsigned int row;
            int dnamecol;
            const char * dname;
            const char * value;
            char * fullname;
            int error = 0;
            hid_t detgpid;

            maxrows = 0;
            dnamecol = -1;
            dname = NULL;
            detgpid = CBF_H5FAIL;

            for (column= 0; column < category->children; column++) {
                if ((category->child[column])->children > maxrows)
                    maxrows=(category->child[column])->children;
                if (cbf_cistrcmp((category->child[column])->name,"id")==0)
                    dnamecol = column;
            }

            for (row = 0; row < maxrows; row++) {

                /*
                 _diffrn_detector.id DETECTORNAME -->
                 /instrument:NXinstrument/CBF_diffrn_detector__DETECTORNAME:NXdetector
                 */

                if (dnamecol==-1 || row >=  (category->child[dnamecol])->children) {

                    dname = "detector";

                } else {

                    handle->node = category->child[dnamecol];

                    handle->row = row;

                    cbf_reportnez(cbf_get_value(handle,&dname),error)


                }

                if (cbf_cistrcmp(dname,"detector")==0) {

                    fullname = (char *)dname;

                } else {

                    cbf_onfailnez(cbf_strcat("CBF_diffrn_detector__",dname,&fullname),
                                  cbf_goto_fast_bookmark(handle,fbkmk))
                }

                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  instGroup,
                                                  instGroupClass,
                                                  h5handle->nxid,
                                                  &instrumentid),error);

                cbf_reportnez(cbf_H5NXGrequire_in_handle(h5handle,
                                                         fullname,
                                                         "NXdetector",
                                                         &detgpid,
                                                         "detector"),error);

                if (fullname != dname) {

                    cbf_reportnez(cbf_free((void **)&fullname,NULL),error);

                }


                for (column= 0; column < category->children; column++) {

                    const char * mappedname;

                    if (cbf_cistrcmp((category->child[column])->name,"type")==0){

                        mappedname = "description";

                    } else if (cbf_cistrcmp((category->child[column])->name,"number_of_axes")==0) {

                        mappedname = (category->child[column])->name;

                    } else if (cbf_cistrcmp((category->child[column])->name,"dtime")==0) {

                        mappedname = "deadtime";

                    } else if (cbf_cistrcmp((category->child[column])->name,"detector")==0) {

                        mappedname = "type";

                    } else if (cbf_cistrcmp((category->child[column])->name,"detector")==0) {

                        mappedname = "type";

                    } else if (column == dnamecol) {

                        continue;

                    } else {

                        mappedname = (category->child[column])->name;

                    }

                    /* no duplicate rows are allowed because each detector
                       name must be unique */

                    if ( H5Lexists(detgpid,mappedname,H5P_DEFAULT)==1) {

                        cbf_onfailnez(CBF_FORMAT,
                        cbf_goto_fast_bookmark(handle,fbkmk));

                    }

                    handle->node = category->child[column];

                    handle->row = row;

                    if (!cbf_get_value(handle,&value) && value) {

                        cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                     mappedname,
                                                                     value,error),
                                      cbf_goto_fast_bookmark(handle,fbkmk));

                    } else {

                        cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                     mappedname,
                                                                     ".",error),
                                      cbf_goto_fast_bookmark(handle,fbkmk));
                    }

                }

            }

            if (detgpid >= 0) H5Gclose(detgpid);

        }


        /* Process diffrn_detector_element category */

		if (!cbf_cistrcmp(category->name,"diffrn_detector_element"))
		{
            unsigned int maxrows;
            unsigned int row;
            int dnamecol, delnamecol;
            const char * dname;
            char * fullname;
            const char * value;
            double doublevalue;
            int error = 0;
            int numeric;
            hid_t detgpid;

            maxrows = 0;
            dnamecol = -1;
            delnamecol = -1;
            numeric = 0;

            dname = NULL;
            delnamecol = -1;
            detgpid = CBF_H5FAIL;

            /* find maximum number of rows, detector id column
               and detector element id column */

            for (column= 0; column < category->children; column++) {
                if ((category->child[column])->children > maxrows)
                    maxrows=(category->child[column])->children;
                if (cbf_cistrcmp((category->child[column])->name,"id")==0)
                    delnamecol = column;
                if (cbf_cistrcmp((category->child[column])->name,"detector_id")==0)
                    dnamecol = column;

            }

            for (row = 0; row < maxrows; row++) {

                int multi_element;

                unsigned int sow;

                const char * ename;

                multi_element = 0;

                /*
                 _diffrn_detector.id DETECTORNAME -->
                 /instrument:NXinstrument/CBF_diffrn_detector__DETECTORNAME:NXdetector
                 */

                if (dnamecol==-1 || row >=  (category->child[dnamecol])->children) {

                    dname = "detector";

                } else {

                    handle->node = category->child[dnamecol];

                    handle->row = row;

                    cbf_reportnez(cbf_get_value(handle,&dname),error);

                    if (!dname) dname = "detector";

                }

                if (cbf_cistrcmp(dname,"detector")==0) {

                    fullname = (char *)dname;

                } else {

                    cbf_failnez(cbf_strcat("CBF_diffrn_detector__",dname,&fullname))
                }

                cbf_reportnez(cbf_require_nxgroup(h5handle,
                                                  instGroup,
                                                  instGroupClass,
                                                  h5handle->nxid,
                                                  &instrumentid),error);

                cbf_reportnez(cbf_H5NXGrequire_in_handle(h5handle,
                                                         fullname,
                                                         "NXdetector",
                                                         &detgpid,
                                                         "detector"),error);

                if (fullname != dname) {

                    cbf_reportnez(cbf_free((void **)&fullname,NULL),error);

                }

                /* check for the multielement case

                 if there is another row with the same detector name,
                 this will be a multielement case to be written by slabs

                 */

                if (maxrows > 1 && dnamecol == -1) {

                    multi_element = 1;

                } else {

                    for (sow = 0; sow < maxrows; sow++ ) {

                        if (sow == row) continue;

                        handle->node = category->child[dnamecol];

                        handle->row = sow;

                        cbf_reportnez(cbf_get_value(handle,&ename),error);

                        if ( (!ename && !cbf_cistrcmp(dname,"detector") )
                            || (ename && !cbf_cistrcmp(ename,dname)) ) {

                            multi_element = 1;

                            break;

                        }

                    }

                }

                for (column= 0; column < category->children; column++) {

                    const char * mappedname;

                    const char * units;

                    if (cbf_cistrcmp((category->child[column])->name,"reference_center_fast")==0){

                        mappedname = "CBF_diffrn_detector_element__reference_center_fast";

                        numeric = 1;

                        units = NULL;

                    } else if (cbf_cistrcmp((category->child[column])->name,"reference_center_slow")==0) {

                        mappedname = "CBF_diffrn_detector_element__reference_center_slow";

                        numeric = 1;

                        units = NULL;

                    } else if (cbf_cistrcmp((category->child[column])->name,"reference_center_units")==0) {

                        mappedname = "CBF_diffrn_detector_element__reference_center_units";

                        numeric = 0;

                        units = NULL;

                    } else if (column==delnamecol) {

                        mappedname = "CBF_diffrn_detector_element__id";

                        numeric = 0;

                        units = NULL;

                    } else if (cbf_cistrcmp((category->child[column])->name,"center[1]")==0){

                        mappedname = "beam_center_x";

                        numeric = 1;

                        units = "mm";

                    } else if (cbf_cistrcmp((category->child[column])->name,"center[2]")==0){

                        mappedname = "beam_center_y";

                        numeric = 1;

                        units = "mm";

                    } else if (column == dnamecol ) {

                        continue;

                    } else {

                        /* until there is support for variants, skip remaining columns */

                        continue;

                    }

                    handle->node = category->child[column];

                    handle->row = row;

                    if (!numeric) {

                        if (!cbf_get_value(handle,&value) && value) {

                            if ( multi_element ) {

                                cbf_onfailnez(error|cbf_add_h5text_dataset_slab (detgpid,
                                                                                 mappedname,
                                                                                 value,
                                                                                 H5S_UNLIMITED,
                                                                                 error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            } else {

                                cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                           mappedname,
                                                                           value,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            }

                        } else {

                            if ( multi_element ) {

                                cbf_onfailnez(error|cbf_add_h5text_dataset_slab (detgpid,
                                                                                 mappedname,
                                                                                 ".",
                                                                                 H5S_UNLIMITED,
                                                                                 error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            } else {

                                cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                           mappedname,
                                                                           ".",error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            }
                        }

                    } else {

                        if (!cbf_get_doublevalue(handle,&doublevalue) ) {

                            if ( multi_element ) {

                                cbf_onfailnez(error|cbf_add_h5double_dataset_slab (detgpid,
                                                                                   mappedname,
                                                                                   doublevalue,
                                                                                   H5S_UNLIMITED,
                                                                                   error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            } else {

                                cbf_onfailnez(error|cbf_add_h5double_dataset(detgpid,
                                                                             mappedname,
                                                                             doublevalue,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            }

                        } else {

                            if ( multi_element ) {

                                cbf_onfailnez(error|cbf_add_h5double_dataset_slab (detgpid,
                                                                                   mappedname,
                                                                                   0.e0,
                                                                                   H5S_UNLIMITED,
                                                                                   error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            } else {

                                cbf_onfailnez(error|cbf_add_h5double_dataset(detgpid,
                                                                             mappedname,
                                                                             0.e0,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk));

                            }
                        }

                        if (units) {

                            hid_t datasetid=CBF_H5FAIL;

                            cbf_h5reportneg(datasetid = H5Dopen(detgpid,mappedname,H5P_DEFAULT),CBF_H5ERROR, error);

                            cbf_failnez(cbf_apply_h5text_attribute(h5handle->colid,
                                                                   "units",units,error));

                            if (cbf_H5Ivalid(datasetid)) H5Dclose(datasetid);

                        }

                    }

                }

            }

            if (detgpid >= 0) H5Gclose(detgpid);

        }
/**** Check for closing instrumentid ****/

        /* Process diffrn_radiation category */

        if (!cbf_cistrcmp(category->name,"diffrn_radiation"))
		{
            unsigned int maxrows;
            unsigned int row;
            const char * value;
            double doublevalue;
            hid_t monochromid;
            int error = 0;
            int numeric;

            maxrows = 0;
            numeric = 0;

            /* find maximum number of rows, detector id column
             and detector element id column */

            for (column= 0; column < category->children; column++) {
                if ((category->child[column])->children > maxrows)
                    maxrows=(category->child[column])->children;
            }

            cbf_reportnez(cbf_require_nxgroup(h5handle,
                                              instGroup,
                                              instGroupClass,
                                              h5handle->nxid,
                                              &instrumentid),error);

            cbf_reportnez(cbf_H5NXGrequire_in_handle(h5handle,
                                                     "monochromator",
                                                     "NXmonochromator",
                                                     &monochromid,
                                                     NULL),error);

            for (row = 0; row < maxrows; row++) {

                int multi_element;

                multi_element = 0;


                  /* check for the multielement case

                 if there is another row with the same detector name,
                 this will be a multielement case to be written by slabs

                 */

                for (column= 0; column < category->children; column++) {

                    const char * mappedname;

                    const char * units;

                    if (cbf_cistrcmp((category->child[column])->name,"wavelength")==0){

                        mappedname = "wavelength";

                        numeric = 1;

                        units = "Angstroms";

                    } else if (cbf_cistrcmp((category->child[column])->name,"reference_center_slow")==0) {

                        mappedname = "CBF_diffrn_detector_element__reference_center_slow";

                        numeric = 1;

                        units = NULL;

                    } else if (cbf_cistrcmp((category->child[column])->name,"reference_center_units")==0) {

                        mappedname = "CBF_diffrn_detector_element__reference_center_units";

                        numeric = 0;

                        units = NULL;


                    } else if (cbf_cistrcmp((category->child[column])->name,"center[1]")==0){

                        mappedname = "beam_center_x";

                        numeric = 1;

                        units = "mm";

                    } else if (cbf_cistrcmp((category->child[column])->name,"center[2]")==0){

                        mappedname = "beam_center_y";

                        numeric = 1;

                        units = "mm";

                    } else {

                        /* until there is support for variants, skip remaining columns */

                        continue;

                    }

                    handle->node = category->child[column];

                    handle->row = row;

                    if (!numeric) {

                        if (!cbf_get_value(handle,&value) && value) {

                            if ( multi_element ) {

                                /* cbf_onfailnez(error|cbf_add_h5text_dataset_slab (detgpid,
                                                                                 mappedname,
                                                                                 value,
                                                                                 H5S_UNLIMITED,
                                                                                 error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            } else {

                                /* cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                           mappedname,
                                                                           value,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            }

                        } else {

                            if ( multi_element ) {

                                /* cbf_onfailnez(error|cbf_add_h5text_dataset_slab (detgpid,
                                                                                 mappedname,
                                                                                 ".",
                                                                                 H5S_UNLIMITED,
                                                                                 error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            } else {

                               /*  cbf_onfailnez(error|cbf_add_h5text_dataset(detgpid,
                                                                           mappedname,
                                                                           ".",error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            }
                        }

                    } else {

                        if (!cbf_get_doublevalue(handle,&doublevalue) ) {

                            if ( multi_element ) {

                                /* cbf_onfailnez(error|cbf_add_h5double_dataset_slab (detgpid,
                                                                                   mappedname,
                                                                                   doublevalue,
                                                                                   H5S_UNLIMITED,
                                                                                   error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            } else {

                                /* cbf_onfailnez(error|cbf_add_h5double_dataset(detgpid,
                                                                             mappedname,
                                                                             doublevalue,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            }

                        } else {

                            if ( multi_element ) {

                                /* cbf_onfailnez(error|cbf_add_h5double_dataset_slab (detgpid,
                                                                                   mappedname,
                                                                                   0.e0,
                                                                                   H5S_UNLIMITED,
                                                                                   error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            } else {

                                /* cbf_onfailnez(error|cbf_add_h5double_dataset(detgpid,
                                                                             mappedname,
                                                                             0.e0,error),
                                              cbf_goto_fast_bookmark(handle,fbkmk)); */

                            }
                        }

                        /* if (units) {

                            hid_t datasetid=CBF_H5FAIL;

                            cbf_h5reportneg(datasetid = H5Dopen(detgpid,mappedname,H5P_DEFAULT),CBF_H5ERROR, error);

                            cbf_failnez(cbf_apply_h5text_attribute(h5handle->colid,
                                                                   "units",units,error));

                            if (cbf_H5Ivalid(datasetid)) H5Dclose(datasetid);

                        } */

                    }

                }

            }

            /* if (detgpid >= 0) H5Gclose(detgpid); */

        }


		if (!cbf_cistrcmp(category->name,"diffrn_radiation"))
		{
			for (column= 0; column < category->children; column++)
			{
				cbf_node * column_node = category->child[column];
				cbf_debug_print2("\t%s",column_node->name);
				if(column_node->children > 1) cbf_debug_print2("warning: too many rows in '%s', only writing first row.\n",category->name);
				if(!cbf_cistrcmp(column_node->name,"div_x_source")) {
					const char * text = 0;
					int error = CBF_SUCCESS;
					cbf_reportnez(cbf_get_columnrow (&text, column_node, 0),error);
					/* check 'text' is suitable for use as an ascii data value */
					cbf_reportnez(cbf_map_h5value("divergence_x", text+1, instGroup, instGroupClass, "collimator", "NXcollimator", 0, 0,
                                                  h5handle),error);
					if (CBF_SUCCESS != error) cbf_debug_print("diffrn_radiation.div_x_source could not be written to nexus file");
				}
				if(!cbf_cistrcmp(column_node->name,"div_y_source")) {
					const char * text = 0;
					int error = CBF_SUCCESS;
					cbf_reportnez(cbf_get_columnrow (&text, column_node, 0),error);
					/* check 'text' is suitable for use as an ascii data value */
					cbf_reportnez(cbf_map_h5value("divergence_y", text+1, instGroup, instGroupClass, "collimator", "NXcollimator", 0, 0,
                                                  h5handle),error);
					if (CBF_SUCCESS != error) cbf_debug_print("diffrn_radiation.div_y_source could not be written to nexus file");
				}
			}
		}
		if (!cbf_cistrcmp(category->name,"diffrn_radiation_wavelength"))
		{
			for (column= 0; column < category->children; column++)
			{
				cbf_node * column_node = category->child[column];
				cbf_debug_print2("\t%s",column_node->name);
				if(column_node->children > 1) cbf_debug_print2( "warning: too many rows in '%s', only writing first row.\n",category->name);
				if(!cbf_cistrcmp(column_node->name,"wavelength")){
					cbf_name_value_pair attr = {"units","Angstroms"};
					const char * text = 0;
					int error = CBF_SUCCESS;
					cbf_reportnez(cbf_get_columnrow (&text, column_node, 0),error);
					/* check 'text' is suitable for use as an ascii data value */
					cbf_reportnez(cbf_map_h5value("wavelength", text+1, instGroup, instGroupClass, "monochromator", "NXmonochromator", 1,
                                                  &attr, h5handle),error);
					if (CBF_SUCCESS != error) cbf_debug_print("diffrn_radiation_wavelength.wavelength could not be written to nexus file");
				}
				if(!cbf_cistrcmp(column_node->name,"wt")) {
					const char * text = 0;
					int error = CBF_SUCCESS;
					cbf_reportnez(cbf_get_columnrow (&text, column_node, 0),error);
					/* check 'text' is suitable for use as an ascii data value */
					cbf_reportnez(cbf_map_h5value("weight", text+1, instGroup, instGroupClass, "monochromator", "NXmonochromator", 0, 0,
                                                  h5handle),error);
					if (CBF_SUCCESS != error) cbf_debug_print("diffrn_radiation_wavelength.wt could not be written to nexus file");
				}
			}
		}


        cbf_failnez(cbf_apply_h5text_attribute(h5handle->catid,
                                               "NX_class","CBF_cbfcat",errorcode));


        /* now, for each column, make it into a group and
         store each row as a dataset */


        for (column= 0; column < category->children; column++)
        {
            /* save the column name in the read bookmark */

            (h5handle->bookmark).column = (category->child[column])->name;


            cbf_h5failneg(h5handle->colid=H5Gcreatex(h5handle->catid,
                                                     (category->child[column])->name?
                                                     (category->child[column])->name:"_(null)_"),
                          CBF_FORMAT);

            cbf_failnez(cbf_apply_h5text_attribute(h5handle->colid,
                                                   "NX_class","CBF_cbfcol",errorcode));

            /* For each row, create a dataset */

            for (row=0; row < category->child [column]->children; row++)
            {

                (h5handle->bookmark).row = row;

                cbf_failnez(cbf_write_h5value(handle,
                                              category->child [column],
                                              row,h5handle));
            }

            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_ARGUMENT);

            h5handle->colid = CBF_H5FAIL;
        }


        if (!cbf_cistrcmp(category->name,"diffrn_scan")) {

            cbf_node * column_node;

            const char * text = 0;

            for (column= 0; column < category->children; column++) {

                column_node = category->child[column];

                if(!cbf_cistrcmp(column_node->name,"id")){

                    if (column_node->children > 1 ) {

                        for (colrow=0; colrow < column_node->children; colrow++) {

                            if(cbf_get_columnrow (&text, column_node, colrow)) {

                                text = " .";

                            }

                            if (cbf_add_h5text_dataset_slab(h5handle->nxid,
                                                              "CBF_scan_id",
                                                              text+1,
                                                              colrow,errorcode)) break;

                        }

                    } else {


                        if(cbf_get_columnrow (&text, column_node, 0)) break;

                        if (!text) break;

                        if(cbf_add_h5text_dataset(h5handle->nxid,
                                                    "CBF_scan_id",text+1,errorcode)) break;

                        break;

                    }

                }
            }
        }

        if (!cbf_cistrcmp(category->name,"entry")) {

            cbf_node * column_node;

            const char * text = 0;

            for (column= 0; column < category->children; column++) {

                column_node = category->child[column];

                if(!cbf_cistrcmp(column_node->name,"id")){

                    if (column_node->children > 1 ) {


                        for (colrow=0; colrow < column_node->children; colrow++) {

                            if(cbf_get_columnrow (&text, column_node, colrow)) {

                                text = " .";

                            }

                            if (cbf_add_h5text_dataset_slab(h5handle->nxid,
                                                              "CBF_entry_id",
                                                              text+1,
                                                              colrow,errorcode)) break;

                        }

                    } else {


                        if(cbf_get_columnrow (&text, column_node, 0)) break;

                        if (!text) break;

                        if(cbf_add_h5text_dataset(h5handle->nxid,
                                                    "CBF_entry_id",text+1,errorcode)) break;

                        break;

                    }

                }
            }
        }

        if (!cbf_cistrcmp(category->name,"diffrn")) {

            cbf_node * column_node;

            const char * text = 0;

            for (column= 0; column < category->children; column++) {

                column_node = category->child[column];

                if(!cbf_cistrcmp(column_node->name,"id")){

                    if (column_node->children > 1 ) {

                        for (colrow=0; colrow < column_node->children; colrow++) {

                            if(cbf_get_columnrow (&text, column_node, colrow)) {

                                text = " .";

                            }

                            if (cbf_add_h5text_dataset_slab(h5handle->nxid,
                                                              "CBF_diffrn_id",
                                                              text+1,
                                                              colrow, errorcode)) break;

                        }

                    } else {


                        if(cbf_get_columnrow (&text, column_node, 0)) break;

                        if (!text) break;

                        if(cbf_add_h5text_dataset(h5handle->nxid,
                                                    "CBF_diffrn_id",text+1,errorcode)) break;

                        break;

                    }

                }
            }
        }

        cbf_failnez(cbf_goto_fast_bookmark(handle,fbkmk));

        /* Success */

        return CBF_SUCCESS;

    }


    /*  create top-level NXentry */

    int cbf_create_NXentry(cbf_h5handle h5handle)
    {

        if (!h5handle ||
            h5handle->nxid >= 0 ||
            h5handle->hfile < 0) return CBF_ARGUMENT;

		cbf_failnez(cbf_h5handle_require_entry(h5handle,0,0));

        h5handle->curnxid=CBF_H5FAIL;

        h5handle->dataid =CBF_H5FAIL;

        return CBF_SUCCESS;

    }


    /*  get the current hdf5 group from the handle */

    int cbf_get_H5groupid(const cbf_h5handle h5handle,
                          hid_t * curnxid) {

        if (!h5handle || !curnxid) return CBF_ARGUMENT;

        if (h5handle->nxid < 0) {

            cbf_failnez(cbf_create_NXentry(h5handle));

        }

        *curnxid = (h5handle->curnxid >= 0)? h5handle->curnxid: h5handle->nxid;

        return CBF_SUCCESS;


    }

    /*  Create an HDF5 Group below NX entry or below curnxid */

    int cbf_H5Gcreate_in_handle(cbf_h5handle h5handle,
                                const char * groupname,
                                hid_t * newgroup)
    {
        hid_t parent;
        
        if (!h5handle) return CBF_ARGUMENT;
        
        if (h5handle->nxid < 0) {
            
            cbf_failnez(cbf_create_NXentry(h5handle));
            
        }

        parent = (h5handle->curnxid >= 0)? h5handle->curnxid: h5handle->nxid;

        cbf_h5failneg(*newgroup=H5Gcreatex(parent,groupname),
                      CBF_FORMAT);

        return CBF_SUCCESS;

    }

    /*  Create an HDF5 NeXus Group below NX entry or below curnxid */

    int cbf_H5NXGcreate(cbf_h5handle h5handle,
                        const char * groupname,
                        const char * nxclass,
                        hid_t * newgroup )
    {
        cbf_failnez(cbf_H5Gcreate_in_handle(h5handle, groupname, newgroup));
        
        cbf_failnez(cbf_apply_h5text_attribute(*newgroup,
                                               "NX_class",nxclass,0));
        
        return CBF_SUCCESS;

    }

    /* Require a group below NXentry or below curnxid
       groupname     -- the final path to be used
       group_id      -- optional pointer to the newly opened group
                        if NULL, no return and the group will be
                        closed
       oldgroupname  -- an optional existing path name or NULL
                  to be renamed to new_name if old_name exists
                  and if groupname does not yet exist

     returns 0 for success
     */
    int cbf_H5Grequire_in_handle(const cbf_h5handle h5handle,
                                 const char * groupname,
                                 hid_t * group_id,
                                 const char * oldgroupname) {

        htri_t gpexists;

        hid_t child_id;

        hid_t parent_id;

        /* Check arguments */

        if (!h5handle || ! groupname) return CBF_ARGUMENT;

        /*  Get (or create) the parent_id */

        cbf_failnez(cbf_get_H5groupid(h5handle,&parent_id));

        /* see if the new name is already there */

        gpexists = H5Lexists(parent_id, groupname, H5P_DEFAULT);

        if (gpexists < 0 || !gpexists ) {

            /* see if the old name is there */

            if (oldgroupname) {

                gpexists = H5Lexists(parent_id, oldgroupname, H5P_DEFAULT);

                if (gpexists < 0 || !gpexists ) {

                    /* Neither path exists, just create the new group */

                    cbf_failnez(cbf_H5Gcreate_in_handle(h5handle,
                                                        groupname,
                                                        group_id));

                    return CBF_SUCCESS;

                } else {

                    /* the old path exists, rename it */

                    cbf_h5failneg(child_id=H5Gopenx(parent_id,oldgroupname),
                                  CBF_FORMAT);

                    cbf_h5failneg(H5Ldelete(parent_id,oldgroupname,H5P_DEFAULT),CBF_FORMAT);

                    if (H5Olink(child_id,parent_id,groupname,
                                H5P_DEFAULT,H5P_DEFAULT)< 0) {

                        H5Olink(child_id,parent_id,oldgroupname,
                                H5P_DEFAULT,H5P_DEFAULT);

                        H5Gclose(child_id);

                        if (*group_id) *group_id = CBF_H5FAIL;

                        return CBF_FORMAT;

                    }

                    if (group_id) {

                        *group_id = child_id;

                    } else {

                        cbf_h5failneg(H5Gclose(child_id),CBF_FORMAT);

                    }

                }

            } else {

                /* create the new group */

                cbf_failnez(cbf_H5Gcreate_in_handle(h5handle,
                                                    groupname,
                                                    group_id));

            }

            return CBF_SUCCESS;

        }

        if (group_id) {

            cbf_h5failneg(*group_id=H5Gopenx(parent_id,groupname),
                          CBF_FORMAT);

            if (*group_id < 0) return CBF_FORMAT;

        }

        return CBF_SUCCESS;

    }

    /* Require NeXus group below NXentry or below curnxid
     groupname     -- the final path to be used
     group_id      -- optional pointer to the newly opened group
     if NULL, no return and the group will be
     closed
     oldgroupname  -- an optional existing path name or NULL
     to be renamed to new_name if old_name exists
     and if groupname does not yet exist

     returns 0 for success
     */
    int cbf_H5NXGrequire_in_handle(const cbf_h5handle h5handle,
                                 const char * groupname,
                                 const char * nxclass,
                                 hid_t * group_id,
                                 const char * oldgroupname) {

        hid_t child_id;

        htri_t aexists;

        if (!h5handle || !groupname || !nxclass) return CBF_ARGUMENT;

        cbf_failnez(cbf_H5Grequire_in_handle(h5handle,
                                             groupname,
                                             &child_id,
                                             oldgroupname));

        aexists = H5Aexists(child_id,"NX_class");

        if (aexists < 0 || !aexists ) {

            cbf_failnez(cbf_apply_h5text_attribute(child_id,
                                               "NX_class",nxclass,0));

        }

        if (group_id) {

            *group_id = child_id;

        } else {

            cbf_h5failneg(H5Gclose(child_id),CBF_FORMAT);

        }

        return CBF_SUCCESS;


    }


    /**
     Checks if the handle appears to be valid, the free's the handle and any data that the handle owns.
     \param h5handle The handle to be free'd.
     \sa cbf_create_h5handle3
     \return An error code
     */
    int cbf_free_h5handle(cbf_h5handle h5handle)
	{
		int error = CBF_SUCCESS;
        int ii;
		if (!h5handle) {
			error |= CBF_ARGUMENT;
		} else {
            void * memblock = (void *) h5handle;
            void * detblock = (void *) h5handle->nxdetectors;
            
            if (cbf_H5Ivalid(h5handle->colid)) {
                CBF_H5CALL(H5Gclose(h5handle->colid));
            }
            
            if (cbf_H5Ivalid(h5handle->catid)) {
                CBF_H5CALL(H5Gclose(h5handle->catid));
            }
            
            if (cbf_H5Ivalid(h5handle->sfid)) {
                CBF_H5CALL(H5Gclose(h5handle->sfid));
            }
            
            if (cbf_H5Ivalid(h5handle->dbid)) {
                CBF_H5CALL(H5Gclose(h5handle->dbid));
            }
            
            if (cbf_H5Ivalid(h5handle->rootid)) {
                CBF_H5CALL(H5Gclose(h5handle->rootid));
            }
            
            if (cbf_H5Ivalid(h5handle->curnxid)) {
                CBF_H5CALL(H5Gclose(h5handle->curnxid));
            }
            
            if (cbf_H5Ivalid(h5handle->dataid)) {
                CBF_H5CALL(H5Gclose(h5handle->dataid));
            }
            
            if (cbf_H5Ivalid(h5handle->nxid)) {
                CBF_H5CALL(H5Gclose(h5handle->nxid));
            }
            
            if (cbf_H5Ivalid(h5handle->nxdata)) {
                CBF_H5CALL(H5Gclose(h5handle->nxdata));
            }
            
            if (cbf_H5Ivalid(h5handle->nxinst)) {
                CBF_H5CALL(H5Gclose(h5handle->nxinst));
            }
            
            if (cbf_H5Ivalid(h5handle->nxsample)) {
                CBF_H5CALL(H5Gclose(h5handle->nxsample));
            }
            
			if (cbf_H5Ivalid(h5handle->nxbeam)) {
				CBF_H5CALL(H5Gclose(h5handle->nxbeam));
			}
            
            for (ii=0; ii< h5handle->num_detectors; ii++) {
                if (cbf_H5Ivalid(h5handle->nxdetectors[ii])) {
                    CBF_H5CALL(H5Gclose(h5handle->nxdetectors[ii]));
                }
            }
            
			if (cbf_H5Ivalid(h5handle->nxgoniometer)) {
				CBF_H5CALL(H5Gclose(h5handle->nxgoniometer));
			}
            
            if (cbf_H5Ivalid(h5handle->nxmonochromator)) {
                CBF_H5CALL(H5Gclose(h5handle->nxmonochromator));
            }
            
			if (cbf_H5Ivalid(h5handle->nxsource)) {
				CBF_H5CALL(H5Gclose(h5handle->nxsource));
			}
            
            if (cbf_H5Ivalid(h5handle->hfile)) {
                CBF_H5CALL(H5Fclose(h5handle->hfile));
            }
            
			free((void*)h5handle->scan_id);
			free((void*)h5handle->sample_id);
            free((void*)h5handle->nxid_name);
            for (ii=0; ii < h5handle->num_detectors; ii++){
                 free((void*)h5handle->nxdetector_names[ii]);
            }
            h5handle->num_detectors = 0;
            if (h5handle->nxdetectors) {
                error |= cbf_free(&detblock,NULL);
            }
			free((void*)h5handle->nxsample_name);
			free((void*)h5handle->nxbeam_name);
			free((void*)h5handle->nxinstrument_name);
			free((void*)h5handle->nxgoniometer_name);
			free((void*)h5handle->nxmonochromator_name);
			free((void*)h5handle->nxsource_name);
            if (h5handle->nxfilename) free((void*)h5handle->nxfilename);
            cbf_free_handle(h5handle->scratch_tables);
			error |= cbf_free(&memblock,NULL);
        }
        return error;
    }

    /* Make an (empty) H5File handle */

    int cbf_make_h5handle(cbf_h5handle *h5handle) {

        cbf_failnez (cbf_alloc ((void **) h5handle, NULL,
                                sizeof(cbf_h5handle_struct), 1));

        (*h5handle)->slice  = 0;
        (*h5handle)->num_detectors  = 0;
        (*h5handle)->hfile   = (hid_t)CBF_H5FAIL;
        (*h5handle)->rootid  = (hid_t)CBF_H5FAIL;
        (*h5handle)->dbid    = (hid_t)CBF_H5FAIL;
        (*h5handle)->sfid    = (hid_t)CBF_H5FAIL;
        (*h5handle)->catid   = (hid_t)CBF_H5FAIL;
		(*h5handle)->colid   = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxid    = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxdata  = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxinst  = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxsample  = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxbeam  = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxdetectors  = NULL;
        (*h5handle)->num_detectors  = 0;
        (*h5handle)->cur_detector  = 0;
		(*h5handle)->nxgoniometer = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxmonochromator = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxsource = (hid_t)CBF_H5FAIL;
        (*h5handle)->curnxid = (hid_t)CBF_H5FAIL;
        (*h5handle)->dataid  = (hid_t)CBF_H5FAIL;
		(*h5handle)->nxid_name = NULL;
		(*h5handle)->nxdetector_names = NULL;
		(*h5handle)->nxsample_name = NULL;
		(*h5handle)->nxbeam_name = NULL;
		(*h5handle)->nxinstrument_name = NULL;
		(*h5handle)->nxgoniometer_name = NULL;
		(*h5handle)->nxmonochromator_name = NULL;
		(*h5handle)->nxsource_name = NULL;
        (*h5handle)->rwmode  = 0;
        (*h5handle)->flags = 0;
#ifdef CBF_USE_ULP
		(*h5handle)->cmp_double_as_float = 0;
		(*h5handle)->float_ulp = 0;
#ifndef NO_UINT64_TYPE
		(*h5handle)->double_ulp = 0;
#endif
#endif
        (*h5handle)->scan_id = NULL;
        (*h5handle)->sample_id = NULL;
#ifdef CBFDEBUG
		(*h5handle)->logfile = stderr;
#else
		(*h5handle)->logfile = NULL;
#endif
        (*h5handle)->nxfilename = NULL;
        cbf_make_handle(&((*h5handle)->scratch_tables));
        return CBF_SUCCESS;

    }

    /* Close the current saveframe in an HDF5 file */

    int cbf_close_h5saveframe (cbf_h5handle h5handle)
    {

        /* Does the node exist? */

        if (!h5handle || h5handle->rootid <0 || h5handle->dbid <0)

            return CBF_ARGUMENT;

        if (h5handle->colid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);

            h5handle->colid = (hid_t)-1;

        }

        if (h5handle->catid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);

            h5handle->catid = (hid_t)-1;

        }

        if (h5handle->sfid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->sfid),CBF_FORMAT);

            h5handle->sfid = (hid_t)-1;

        }

        return CBF_SUCCESS;
    }


    /* Write a saveframe name to an HDF5 file
     Make a new group of NeXus class CBF_cbfsf
     in the CBF_cbf current datablock
     */

    int cbf_write_h5saveframename (const cbf_node *saveframe,
                                   cbf_h5handle h5handle)
    {

        /* Does the node exist? */

        if (!saveframe || !h5handle || h5handle->rootid <0 || h5handle->dbid <0)

            return CBF_ARGUMENT;

        /* If another saveframe is open, close all its children
         and the saveframe itself */

        if (h5handle->sfid >= 0) {

            cbf_failnez(cbf_close_h5saveframe(h5handle));

        }


        /* Write the name */

        cbf_h5failneg(h5handle->sfid=H5Gcreatex(h5handle->dbid,
                                                saveframe->name),
                      CBF_FORMAT);

        cbf_failnez(cbf_apply_h5text_attribute(h5handle->sfid,
                                               "NX_class", "CBF_cbfsf",0));

        return CBF_SUCCESS;
    }




    /* Write a datablock name to an HDF5 file
     Make a new group of NeXus class CBF_cbfdb in the CBF_cbf class root
     */

    int cbf_write_h5datablockname (const cbf_node *datablock, cbf_h5handle h5handle)
    {

        /* Does the node exist? */

        if (!datablock || !h5handle || h5handle->rootid <0)

            return CBF_ARGUMENT;

        /* If another datablock is open, close all its children
         and the datablock itself */

        if (h5handle->colid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);

            h5handle->colid = (hid_t)-1;

        }

        if (h5handle->catid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);

            h5handle->catid = (hid_t)-1;

        }

        if (h5handle->sfid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->sfid),CBF_FORMAT);

            h5handle->sfid = (hid_t)-1;

        }

        if (h5handle->dbid >= 0) {

            cbf_h5failneg(H5Gclose(h5handle->dbid),CBF_FORMAT);

            h5handle->dbid = (hid_t)-1;

        }

        /* save the datablock name in the read bookmark */

        (h5handle->bookmark).datablock = datablock->name;


        /* Write the name */

        cbf_h5failneg(h5handle->dbid=H5Gcreatex(h5handle->rootid,
                                                datablock->name),
                      CBF_FORMAT);

        cbf_failnez(cbf_apply_h5text_attribute(h5handle->dbid,
                                               "NX_class", "CBF_cbfdb",0));

        return CBF_SUCCESS;
    }


    /* Write a node to an HDF5 file */

    int cbf_write_h5node (cbf_handle handle, const cbf_node *node,
                          const cbf_h5handle h5handle)
    {
        unsigned int count;


        /* Follow any links */

        node = cbf_get_link (node);


        /* Does the node exist? */

        if (!node)

            return CBF_ARGUMENT;

        /* Node type */

        switch (node->type)
        {


                /* For the root, start the file with a CBF group */

            case CBF_ROOT:

                break;

            case CBF_DATABLOCK:

                if (h5handle->rootid < 0) return CBF_FORMAT;

                cbf_failnez (cbf_write_h5datablockname (node, h5handle))

                break;

            case CBF_CATEGORY:

                cbf_failnez (cbf_write_h5category (handle, node, h5handle))

                break;

            case CBF_SAVEFRAME:

                cbf_failnez (cbf_write_h5saveframename (node, h5handle))

                break;


            default:

                return CBF_ARGUMENT;
        }


        /* Write the children */

        if (node->type == CBF_ROOT || node->type == CBF_DATABLOCK || node->type == CBF_SAVEFRAME)

            for (count = 0; count < node->children; count++)
            {

                cbf_failnez (cbf_write_h5node (handle, node->child [count], h5handle))

            }

        if (node->type == CBF_SAVEFRAME) {

            cbf_failnez(cbf_close_h5saveframe(h5handle));

        }


        /* Flush the buffers */

        cbf_h5failneg(H5Fflush(h5handle->hfile,H5F_SCOPE_LOCAL),CBF_ARGUMENT);

        return CBF_SUCCESS;


    }



    /* Create an HDF5 File handle */

    int cbf_create_h5handle(cbf_h5handle *h5handle,const char * h5filename)
	{
        hid_t fcreate_prop_list;

        cbf_failnez(cbf_make_h5handle(h5handle));

        cbf_h5onfailneg(fcreate_prop_list = H5Pcreate(H5P_FILE_ACCESS),
                        CBF_ALLOC,cbf_free((void**) h5handle, NULL));

        (*h5handle)->rwmode = 1;

        cbf_h5onfailneg(H5Pset_fclose_degree(fcreate_prop_list,H5F_CLOSE_STRONG),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        cbf_h5onfailneg((*h5handle)->hfile = H5Fcreate(h5filename,H5F_ACC_TRUNC,
                                                       H5P_DEFAULT,fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        cbf_h5onfailneg(H5Pclose(fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        cbf_onfailnez(cbf_H5Gcreate_in_handle(*h5handle,"CBF_cbf",
                                              &((*h5handle)->rootid)),
                      cbf_free_h5handle(*h5handle));

        cbf_failnez(cbf_apply_h5text_attribute((*h5handle)->rootid,"NX_class",
                                               "CBF_cbf",0));


        return CBF_SUCCESS;

	}

    int cbf_require_h5handle_filename(cbf_h5handle h5handle) {
        
        char * filename;
        
        ssize_t filesize;
        
        if (!h5handle || !cbf_H5Ivalid(h5handle->nxid)) return CBF_ARGUMENT;
        
        filesize = H5Fget_name(h5handle->nxid,NULL,0);
        
        if (filesize <= 0) return CBF_NOTFOUND;
        
        cbf_failnez(cbf_alloc(((void **) &filename),NULL,
                              1,filesize+1));
        
        if (H5Fget_name(h5handle->nxid,filename,filesize+1)==filesize) {
            
            h5handle -> nxfilename = filename;
            
            return CBF_SUCCESS;
        }
        
        cbf_failnez(cbf_free(((void **) &filename),NULL));
        
        return CBF_H5ERROR;
    
    }

	/* Create an HDF5 File handle without adding an CBF_cbf group to it */

	int cbf_create_h5handle2(cbf_h5handle *h5handle,const char * h5filename)
	{
		hid_t fcreate_prop_list;

        char verstring[] = CBF_VERS_STRING;
        
        char svnrev[] = CBF_SVN_REVISION_STRING;
        
        char svndate[] = CBF_SVN_DATE_STRING;
        
        char buffer[140];
        
        int ii, irev, idate;

        int error = CBF_SUCCESS;

		cbf_failnez(cbf_make_h5handle(h5handle));

		cbf_h5onfailneg(fcreate_prop_list = H5Pcreate(H5P_FILE_ACCESS),
                        CBF_ALLOC,cbf_free((void**) h5handle, NULL));

		(*h5handle)->rwmode = 1;

		cbf_h5onfailneg(H5Pset_fclose_degree(fcreate_prop_list,H5F_CLOSE_STRONG),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

		cbf_h5onfailneg((*h5handle)->hfile = H5Fcreate(h5filename,H5F_ACC_TRUNC,
                                                       H5P_DEFAULT,fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

		cbf_h5onfailneg(H5Pclose(fcreate_prop_list), CBF_ARGUMENT,
                        cbf_free((void**) h5handle, NULL));

		CBF_CALL(cbf_H5Arequire_string((*h5handle)->hfile,"NX_class","NXroot"));
		CBF_CALL(cbf_H5Arequire_string((*h5handle)->hfile,"creator","CBFlib"));
        buffer[0] = '\0';
        
        strncat(buffer,verstring,50);
        for (ii=strlen(svnrev)-1; ii >= 0; ii--) {
            if (svnrev[ii] == '$' || svnrev[ii] == ' ') {
                svnrev[ii] = '\0';
            } else break;
        }
        irev = 0;
        if (strlen(svnrev)>0 && svnrev[0]=='$') irev++;
        for (ii=0; ii < strlen(svnrev); ii++) {
            if (svnrev[ii]==':') {
                irev = ii+1;
                if (ii < strlen(svnrev)-1 && svnrev[ii+1]==' ') irev++;
                break;
            }
        }
        for (ii=strlen(svndate)-1; ii >= 0; ii--) {
            if (svndate[ii] == '$' || svndate[ii] == ' ') {
                svndate[ii] = '\0';
            } else break;
        }
        idate = 0;
        if (strlen(svndate)>0 && svndate[0]=='$') idate++;
        for (ii=0; ii < strlen(svndate); ii++) {
            if (svndate[ii]==':') {
                idate = ii+1;
                if (ii < strlen(svndate)-1 && svndate[ii]==' ') idate++;
                break;
            }
        }

        strncat(buffer," (r",3);
        strncat(buffer,svnrev+irev,10);
        strncat(buffer,") ",2);
        strncat(buffer,svndate+idate,50);
		CBF_CALL(cbf_H5Arequire_string((*h5handle)->hfile,"creator_version", 
            buffer));
		return error;
	}

	/**
     This function expects the user to create or open a hdf5 file with the appropriate parameters for what they are
     trying to do, replacing older functions which would create a file with the <code>H5F_ACC_TRUNC</code> flag and
     <code>H5F_CLOSE_STRONG</code> property.

     \param handle A pointer to a handle which is to be allocated.
     \param file A HDF5 file to store within the newly created handle.
     \sa cbf_free_h5handle
     \return An error code
     */
	int cbf_create_h5handle3
    (cbf_h5handle * handle,
     hid_t file)
	{
		int error = CBF_SUCCESS;
		if (!handle) {
			error |= CBF_ARGUMENT;
		} else {
			CBF_CALL(cbf_make_h5handle(handle));
			CBF_CALL(cbf_h5handle_set_file(*handle,file));
		}
		return error;
	}
    
    
    /*  Write cbf to HDF5 file hfile 

	Should check the type of CBF file we have (miniCBF [+header convention, eventually...] vs full CBF) and call the appropriate function.
	*/
    int cbf_write_h5file (cbf_handle handle, cbf_h5handle h5handle, int flags)
    {
		cbf_node *node = NULL;

        int errorcode = CBF_SUCCESS;

        if (!handle || !h5handle)

            return CBF_ARGUMENT;

        /* Transfer the flags into h5handle */

        h5handle->flags = flags;

        /* Find the root node */

		cbf_failnez (cbf_find_parent (&node, handle->node, CBF_ROOT));

        /* Reset the reference counts */

		cbf_failnez( cbf_reset_refcounts(handle->dictionary) );

		/* ensure the handle contains some basic structure */

		cbf_reportnez(cbf_h5handle_require_entry(h5handle,0,0), errorcode);
		cbf_reportnez(cbf_h5handle_require_instrument(h5handle,0,0), errorcode);

		/* Do the mappings from CBF to nexus */

		/* Write the CBF data into the file in a special node to keep
         it separate from actual mappings */

        errorcode = cbf_write_h5node (handle, node, h5handle);

        if (!errorcode) {

            cbf_write_h5nxaxes(handle, h5handle);

        }

        return errorcode;

	}

	/*
     cbf_write_nx2cbf__<NXclass>
     Write the nexus class, recursively, from the given handle into a cbf handle
     
     Need to record which tables have been created already, and provide methods to create
     any new tables I need. If a table has been created it will have a node in the CBF
     tree, I can store either this node or NULL to find out if it exists. I always know
     which table I want to create, so can call the appropriate function without needing
     a run-time lookup from a list of creation functions.
     
     I need a list of table nodes and a list of shared keys to make this work. Like the
     'cbf_nx2cbf_key_t' this can be removed and replaced with function-specific parameters once
     they are known.
     */

	typedef enum cbf_axisEquipment_e
	{
		/* actual physical equipment */
		axisEquipment_detector,
		axisEquipment_image,
		axisEquipment_goniometer,
		/* special values */
		axisEquipment_gravity,
		axisEquipment_source,
		/* other/undefined */
		axisEquipment_general
	} cbf_axisEquipment_e;
    
	typedef struct cbf_axisData_t
	{
		const char * name;
		hid_t axis;
		cbf_axisEquipment_e equipment;
        int flags;
		struct cbf_axisData_t * depends_on;
        struct cbf_axisData_t * rotation_axis;
	} cbf_axisData_t;
    
#define CBF_AXIS_DATA_PGA  1   /* Flag bit for primary goniometer axis */

	/*
     Allocate and initialise a new 'cbf_axisData_t' object.
     */
	static int _cbf_create_axisData_t
    (cbf_axisData_t *  * const axisData)
	{
		int error = CBF_SUCCESS;
		if (!axisData) {
			error |= CBF_ARGUMENT;
		} else if (!(*axisData=malloc(sizeof(cbf_axisData_t)))) {
			error |= CBF_ALLOC;
		} else {
			cbf_axisData_t * const data = *axisData;
			data->name = NULL;
			data->axis = CBF_H5FAIL;
			data->equipment = axisEquipment_general;
            data->flags = 0;
			data->depends_on = NULL;
            data->rotation_axis = NULL;
		}
		return error;
	}

	/*
     Free 'cbf_axisData_t' object and all associated memory.
     */
	static int _cbf_free_axisData_t
    (cbf_axisData_t * const axisData)
	{
		int error = CBF_SUCCESS;
		if (!axisData) {
			error |= CBF_ARGUMENT;
		} else {
			free((void*)axisData->name);
			cbf_H5Dfree(axisData->axis);
			free((void*)axisData);
		}
		return error;
	}

	typedef struct cbf_nx2cbf_key_t
	{
		/*
         keys - should not be modified once created.
         */
		const char * array_id;
		int binary_id;
		const char * datablock_id;
		const char * diffrn_id;
		const char * diffrn_detector_id;
		const char * diffrn_detector_element_id;
		const char * diffrn_measurement_id;
		const char * frame_id;
		const char * scan_id;
		const char * wavelength_id;
		/*
         tables - should be modified as data is added and
         will be modified when the table is first created.
         */
		cbf_node * array_data;
		cbf_node * array_element_size;
		cbf_node * array_intensities;
		cbf_node * diffrn;
		cbf_node * diffrn_data_frame;
		cbf_node * diffrn_detector;
		cbf_node * diffrn_detector_element;
		cbf_node * diffrn_measurement;
		cbf_node * diffrn_radiation;
		cbf_node * diffrn_radiation_wavelength;
		cbf_node * diffrn_scan;
		cbf_node * diffrn_scan_frame;
		cbf_node * diffrn_source;
		/*
         number of frames of data in the file - many array
         data items must be scalar, have 1 element or be
         this length.
         */
		hsize_t frames;
		hsize_t xdim;
		hsize_t ydim;
		/* axes */
		cbf_axisData_t * * axisData;
		size_t nAxes;
		/* other data */
		int has_scaling_factor;
		int has_offset;
		unsigned int indent;
	} cbf_nx2cbf_key_t;

	static int _cbf_create_nx2cbf_key
    (cbf_nx2cbf_key_t * const key)
	{
		int error = CBF_SUCCESS;
		if (!key) {
			error |= CBF_ARGUMENT;
		} else {
			/* keys */
			key->array_id = NULL;
			key->binary_id = 0;
			key->datablock_id = NULL;
			key->diffrn_id = NULL;
			key->diffrn_detector_id = NULL;
			key->diffrn_detector_element_id = NULL;
			key->diffrn_measurement_id = NULL;
			key->frame_id = NULL;
			key->scan_id = NULL;
			key->wavelength_id = NULL;
			/* tables */
			key->array_data = NULL;
			key->array_element_size = NULL;
			key->array_intensities = NULL;
			key->diffrn = NULL;
			key->diffrn_data_frame = NULL;
			key->diffrn_detector = NULL;
			key->diffrn_detector_element = NULL;
			key->diffrn_measurement = NULL;
			key->diffrn_radiation = NULL;
			key->diffrn_radiation_wavelength = NULL;
			key->diffrn_scan = NULL;
			key->diffrn_scan_frame = NULL;
			key->diffrn_source = NULL;
			/* other */
			key->frames = 0;
			key->xdim = 0;
			key->ydim = 0;
			key->axisData = NULL;
			key->nAxes = 0;
			key->has_scaling_factor = 0;
			key->has_offset = 0;
			key->indent = 0;
		}
		return error;
	}
    
	static int _cbf_free_nx2cbf_key
    (cbf_nx2cbf_key_t * const key)
	{
		int error = CBF_SUCCESS;
		if (!key) {
			error |= CBF_ARGUMENT;
		} else {
			cbf_axisData_t * const * it = key->axisData;
			cbf_axisData_t * const * const end = key->axisData+key->nAxes;
			for (; end != it; ++it) {
				error |= _cbf_free_axisData_t(*it);
			}
			free((void*)key->axisData);
		}
		return error;
	}
    
	static int _cbf_nx2cbf_key_require_axis
    (cbf_nx2cbf_key_t * const key, /* key object to add the axis too */
     cbf_axisData_t * * const newAxisData, /* place to store a pointer to the new or existing axis data */
     const hid_t axis, /* the HDF5 dataset where the axis is stored */
     const char * const name, /* a name for the axis */
     cbf_axisEquipment_e equipment /* CBF's 'axis.equipment' data item */)
	{
		int error = CBF_SUCCESS;
		if (!key || !cbf_H5Ivalid(axis) || !name) {
			error |= CBF_ARGUMENT;
		} else {
			cbf_axisData_t * const * it = key->axisData;
			cbf_axisData_t * const * const end = key->axisData+key->nAxes;
			/* search the list of axes for the dataset */
			for (; end != it; ++it) {
				const htri_t cmp = cbf_H5Ocmp((*it)->axis,axis);
				if (cmp < 0) error |= CBF_H5ERROR;
				else if (!cmp) break;
			}
			/* if not found, add it */
			if (end==it) {
				const size_t nAxes = key->nAxes;
				cbf_axisData_t * * const axisData = realloc(key->axisData,sizeof(cbf_axisData_t*)*(1+key->nAxes));
				if (!axisData) {
					error |= CBF_ALLOC;
				} else {
					++key->nAxes;
					key->axisData = axisData;
					if (CBF_SUCCESS!=(error|=_cbf_create_axisData_t(axisData+nAxes))) {
                        cbf_debug_print(cbf_strerror(error));
 					} else {
						cbf_axisData_t * const data = axisData[nAxes];
						*newAxisData = data;
						data->axis = axis;
						data->name = _cbf_strdup(name);
						data->equipment = equipment;
					}
				}
			} else {
				*newAxisData = *it;
			}
		}
		return error;
	}
    
	/*
     Declare a bunch of table manipulation functions, because they call each other to ensure everything is defined.
     TODO: Update these to return successfully if a row with the given keys already exists,
     to prevent problems where duplicate rows could be created.
     */
	static int _cbf_nx2cbf_table__array_data
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__array_intensities
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_data_frame
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_detector
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_detector_element
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_measurement
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_radiation
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_radiation_wavelength
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_scan
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_scan_frame
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
	static int _cbf_nx2cbf_table__diffrn_source
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table);
    
	static int _cbf_nx2cbf_table__array_data
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->array_id || !table->binary_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->array_data;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"array_data"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"array_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->array_id));
				CBF_CALL(cbf_require_column(cbf,"binary_id"));
				CBF_CALL(cbf_set_integervalue(cbf,table->binary_id));
                
				/* ensure foreign keys are well-defined */
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
		}

	static int _cbf_nx2cbf_table__array_intensities
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;

		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->array_id || !table->binary_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->array_intensities;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"array_intensities"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"array_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->array_id));
				CBF_CALL(cbf_require_column(cbf,"binary_id"));
				CBF_CALL(cbf_set_integervalue(cbf,table->binary_id));
                
				/* ensure foreign keys are well-defined */
			}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
	}
    
	static int _cbf_nx2cbf_table__diffrn
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
		{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->diffrn_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_id));
                
				/* ensure foreign keys are well-defined */
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}

		return error;
		}

	static int _cbf_nx2cbf_table__diffrn_data_frame
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->diffrn_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_data_frame;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_data_frame"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->frame_id));
				CBF_CALL(cbf_require_column(cbf,"array_id"));
				CBF_CALL(cbf_set_value(cbf,table->array_id));
				CBF_CALL(cbf_require_column(cbf,"binary_id"));
				CBF_CALL(cbf_set_integervalue(cbf,table->binary_id));
				CBF_CALL(cbf_require_column(cbf,"detector_element_id"));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_detector_element_id));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn_detector_element(cbf,nx,table));
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}

		return error;
	}

	static int _cbf_nx2cbf_table__diffrn_detector
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;

		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->diffrn_id || !table->diffrn_detector_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_detector;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_detector"));
				*node = cbf->node;

				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"diffrn_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_id));
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_detector_id));

				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn(cbf,nx,table));
			}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
	}
    
	static int _cbf_nx2cbf_table__diffrn_detector_element
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->diffrn_detector_id || !table->diffrn_detector_element_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_detector_element;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_detector_element"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_detector_element_id));
				CBF_CALL(cbf_require_column(cbf,"detector_id"));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_detector_id));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
		}

	static int _cbf_nx2cbf_table__diffrn_measurement
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;

		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->diffrn_id || !table->diffrn_measurement_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_measurement;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_measurement"));
				*node = cbf->node;

				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"diffrn_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_id));
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_measurement_id));

				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn(cbf,nx,table));
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}

		return error;
		}

	static int _cbf_nx2cbf_table__diffrn_radiation
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->diffrn_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_radiation;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_radiation"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"diffrn_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_id));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn(cbf,nx,table));
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}

		return error;
		}

	static int _cbf_nx2cbf_table__diffrn_radiation_wavelength
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->diffrn_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_radiation_wavelength;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_radiation_wavelength"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->wavelength_id));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
				CBF_CALL(cbf_require_column(cbf,"wavelength_id"));
				CBF_CALL(cbf_set_value(cbf,table->wavelength_id));
			}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
	}

	static int _cbf_nx2cbf_table__diffrn_scan
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;

		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->scan_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_scan;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_scan"));
				*node = cbf->node;

				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->scan_id));
                
				/* ensure foreign keys are well-defined */
			}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
	}
    
	static int _cbf_nx2cbf_table__diffrn_scan_frame
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;
        
		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!nx) {
			cbf_debug_print("invalid NeXus handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->datablock_id || !table->frame_id || !table->scan_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_scan_frame;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_scan_frame"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"frame_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->frame_id));
				CBF_CALL(cbf_require_column(cbf,"scan_id"));
				CBF_CALL(cbf_set_value(cbf,table->scan_id));
				CBF_CALL(cbf_require_column(cbf,"frame_number"));
				CBF_CALL(cbf_set_integervalue(cbf,1+nx->slice));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn_scan(cbf,nx,table));
				CBF_CALL(_cbf_nx2cbf_table__diffrn_data_frame(cbf,nx,table));
		}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
		}

	static int _cbf_nx2cbf_table__diffrn_source
    (const cbf_handle cbf,
     const cbf_h5handle nx,
     cbf_nx2cbf_key_t * const table)
	{
		int error = CBF_SUCCESS;

		/* check arguments */
		if (!cbf) {
			cbf_debug_print("invalid CBF handle given");
			error |= CBF_ARGUMENT;
		} else if (!table || !table->diffrn_id) {
			cbf_debug_print("invalid table list given");
			error |= CBF_ARGUMENT;
		} else {
			cbf_node * * const node = &table->diffrn_source;
			if (!*node) {
				/* create the table & store the node */
				CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
				CBF_CALL(cbf_require_category(cbf,"diffrn_source"));
				*node = cbf->node;
                
				/* populate the table with all the required keys */
				CBF_CALL(cbf_require_column(cbf,"diffrn_id"));
				CBF_CALL(cbf_new_row(cbf));
				CBF_CALL(cbf_set_value(cbf,table->diffrn_id));
                
				/* ensure foreign keys are well-defined */
				CBF_CALL(_cbf_nx2cbf_table__diffrn(cbf,nx,table));
			}
			/* set the handle to a sensible state */
			cbf->node = *node;
		}
        
		return error;
	}
    
		/*
     Function to read a scalar string from a dataset
		*/
	static int _cbf_nx2cbfDread_scalar_string
    (const hid_t data,
     const char * * const value)
	{
		int error = CBF_SUCCESS;
		if (!cbf_H5Ivalid(data) || !value) error |= CBF_ARGUMENT;
		if (CBF_SUCCESS==error) {
			hid_t data_type = CBF_H5FAIL;
			H5T_class_t data_class = H5T_NO_CLASS;
			if ((data_type=H5Dget_type(data))<0) {
				cbf_debug_print("Couldn't get type of dataset");
				error |= CBF_H5ERROR;
			} else if (H5T_NO_CLASS==(data_class=H5Tget_class(data_type))) {
				cbf_debug_print("Couldn't get class of datatype");
				error |= CBF_H5ERROR;
			} else if (H5T_STRING!=data_class) {
				cbf_debug_print("Wrong class of datatype");
				error |= CBF_H5DIFFERENT;
			} else {
				const htri_t vlstr = H5Tis_variable_str(data_type);
				char * lvalue = NULL;
				if (vlstr<0) {
					cbf_debug_print("Couldn't check for a variable-length string");
					error |= CBF_H5ERROR;
				} else if (vlstr) {
					/* I have a variable-length string */
					if (H5Dread(data,data_type,H5S_ALL,H5S_ALL,H5P_DEFAULT,&lvalue)<0) {
						cbf_debug_print("Couldn't read string");
						error |= CBF_H5ERROR;
					}
				} else {
					/* I have a fixed-length string */
					const size_t len = H5Tget_size(data_type);
					if (!len) {
						cbf_debug_print("Couldn't get length of string");
						error |= CBF_H5ERROR;
					} else if (!(lvalue=malloc(len))) {
						cbf_debug_print(cbf_strerror(CBF_ALLOC));
						error |= CBF_ALLOC;
					} else if (H5Dread(data,data_type,H5S_ALL,H5S_ALL,H5P_DEFAULT,lvalue)<0) {
						cbf_debug_print("Couldn't read string");
						error |= CBF_H5ERROR;
					}
				}
				if (CBF_SUCCESS==error) *value = lvalue;
			}
			cbf_H5Tfree(data_type);
		}
		return error;
	}

    
	typedef struct op_data_t
	{
		cbf_h5handle nx;
		cbf_handle cbf;
		cbf_nx2cbf_key_t * const table;
	} op_data_t;

	static void _cbf_write_name
    (FILE * const out,
     const char * const name,
     const char * const class,
     unsigned int indent,
     const unsigned int processed)
	{
		while (indent--) fputc('\t',out);
		if (!class) {
			if (!processed) fprintf(out,"✗ %s\n",name);
			else if (1==processed) fprintf(out,"✔ %s\n",name);
			else fprintf(out,"- %s\n",name);
		} else {
			if (!processed) fprintf(out,"✗ %s:%s\n",name,class);
			else if (1==processed) fprintf(out,"✔ %s:%s\n",name,class);
			else fprintf(out,"- %s:%s\n",name,class);
		}
	}

	static int cbf_write_nx2cbf__detector_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"beam_center_x")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							double value = 0., factor = 0./0.;
							const int rank = H5Sget_simple_extent_ndims(data_space);
							if (0==rank) {
								/* read the value */
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
							} else if (1==rank) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
		}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
							if (CBF_SUCCESS==error) {
								/* convert the data to the correct units */
								hid_t units = CBF_H5FAIL;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
							}
							/* ensure I have suitable structure within the CBF file */
							CBF_CALL(_cbf_nx2cbf_table__diffrn_detector_element(cbf,nx,table));
							CBF_CALL(cbf_require_column(cbf,"center[1]"));
							/* write the data */
							CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"beam_center_y")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							double value = 0., factor = 0./0.;
							const int rank = H5Sget_simple_extent_ndims(data_space);
							if (0==rank) {
								/* read the value */
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
							} else if (1==rank) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
							if (CBF_SUCCESS==error) {
								/* convert the data to the correct units */
								hid_t units = CBF_H5FAIL;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
							}
							/* ensure I have suitable structure within the CBF file */
							CBF_CALL(_cbf_nx2cbf_table__diffrn_detector_element(cbf,nx,table));
							CBF_CALL(cbf_require_column(cbf,"center[2]"));
							/* write the data */
							CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"CBF_diffrn_data_frame__details")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							const char * value = NULL;
							const int rank = H5Sget_simple_extent_ndims(data_space);
							/* check rank, allowing for multiple usable results */
							if (0==rank) {
								/* read the value */
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
							} else if (1==rank) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hid_t vlstr = CBF_H5FAIL;
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									CBF_CALL(cbf_H5Tcreate_string(&vlstr,H5T_VARIABLE));
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,vlstr));
									cbf_H5Tfree(vlstr);
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
							/* convert the data to the correct units: no-op */
							/* ensure I have suitable structure within the CBF file */
							CBF_CALL(_cbf_nx2cbf_table__diffrn_data_frame(cbf,nx,table));
							CBF_CALL(cbf_require_column(cbf,"details"));
							/* write the data */
							CBF_CALL(cbf_set_value(cbf,value));
							free((void*)value);
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"count_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0., factor = 0./0.;
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									if (CBF_SUCCESS==error) {
										/* convert the data to the correct units */
										hid_t units = CBF_H5FAIL;
										const char * unit_string = NULL;
										CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(units,&unit_string));
										CBF_CALL(cbf_scale_units(unit_string,"s",&factor));
										free((void*)unit_string);
										cbf_H5Afree(units);
									}
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_scan_frame(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"integration_time"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"data")) {
						int indent = table->indent;
						if (nx->logfile) {
							while (indent--) fputc('\t',nx->logfile);
							fprintf(nx->logfile,"- %s\n",name);
						}
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"dead_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								double value = 0., factor = 0./0.;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								if (CBF_SUCCESS==error) {
									/* convert the data to the correct units */
									hid_t units = CBF_H5FAIL;
									const char * unit_string = NULL;
									CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
									CBF_CALL(cbf_H5Aread_string(units,&unit_string));
									CBF_CALL(cbf_scale_units(unit_string,"us",&factor));
									free((void*)unit_string);
									cbf_H5Afree(units);
								}
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"dtime"));
								/* write the data */
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"description")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								if (CBF_SUCCESS==error) {
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"type"));
									/* write the data */
									CBF_CALL(cbf_set_value(cbf,value));
								}
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"details")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								if (CBF_SUCCESS==error) {
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"details"));
									/* write the data */
									CBF_CALL(cbf_set_value(cbf,value));
								}
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"depends_on")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * path = NULL;
								cbf_axisData_t * prevAxisPtr = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&path));
								while (CBF_SUCCESS==error && path && strcmp(path,".")) {
									/*
                                     Given the path to an axis dataset, I want to extract
                                     all relevant details and write them out to the CBF file.
                                     */
									hid_t axis = CBF_H5FAIL;
									if (!cbf_H5Ivalid(axis=H5Dopen2(g_id, path, H5P_DEFAULT))) {
										cbf_debug_print("couldn't open dataset");
										error |= CBF_H5ERROR;
									} else {
										const char * _path = NULL;
										hid_t depends_on = CBF_H5FAIL;
										cbf_axisData_t * axisPtr = NULL;
										const char * const chr = strrchr(path,'/');
										const char * const name = NULL==chr ? path : 1+chr;
										CBF_CALL(_cbf_nx2cbf_key_require_axis(table,&axisPtr,axis,name,axisEquipment_detector));
										CBF_CALL(cbf_H5Afind(axis,&depends_on,"depends_on",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(depends_on,&_path));
										if (CBF_SUCCESS==error) {
											/* set dependency of previous axis */
											if (prevAxisPtr) prevAxisPtr->depends_on = axisPtr;
											/* some axes are shared with other peices of equipment, set the type appropriately */
											if (axisEquipment_image==axisPtr->equipment) axisPtr->equipment = axisEquipment_detector;
											if (axisEquipment_detector!=axisPtr->equipment) axisPtr->equipment = axisEquipment_general;
										} else {
											cbf_H5Dfree(axis);
										}
										/* housekeeping: update the previous axis and path */
										prevAxisPtr = axisPtr;
										free((void*)path);
										path = _path;
										/* ensure hdf5 stuff is closed */
										cbf_H5Afree(depends_on);
									}
								}
								free((void*)path);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"distance")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0., factor = 0./0.;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									if (CBF_SUCCESS==error) {
										/* convert the data to the correct units */
										hid_t units = CBF_H5FAIL;
										const char * unit_string = NULL;
										CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(units,&unit_string));
										CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
										free((void*)unit_string);
										cbf_H5Afree(units);
									}
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"sample_detector_distance"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"frame_start_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hid_t vlstr = CBF_H5FAIL;
									hsize_t offset[] = {nx->slice};
									hsize_t count[] = {1};
									const char * value = NULL;
									CBF_CALL(cbf_H5Tcreate_string(&vlstr,H5T_VARIABLE));
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,vlstr));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_scan_frame(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"date"));
									/* write the data */
									CBF_CALL(cbf_set_value(cbf,value));
									free((void*)value);
									cbf_H5Tfree(vlstr);
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"frame_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0., factor = 0./0.;
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									if (CBF_SUCCESS==error) {
										/* convert the data to the correct units */
										hid_t units = CBF_H5FAIL;
										const char * unit_string = NULL;
										CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(units,&unit_string));
										CBF_CALL(cbf_scale_units(unit_string,"s",&factor));
										free((void*)unit_string);
										cbf_H5Afree(units);
									}
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_scan_frame(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"time_period"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"gain_setting")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"gain_setting"));
								/* write the data */
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"offset")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"offset"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value));
									if (CBF_SUCCESS==error) table->has_offset = 1;
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"saturation_value")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									int value = 0;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_INT));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"overload"));
									/* write the data */
									CBF_CALL(cbf_set_integervalue(cbf,value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"scaling_factor")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"scaling"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value));
									if (CBF_SUCCESS==error) table->has_scaling_factor = 1;
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"sensor_material")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"sensor_material"));
								/* write the data */
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"sensor_thickness")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								double value = 0., factor = 0./0.;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								if (CBF_SUCCESS==error) {
									/* convert the data to the correct units */
									hid_t units = CBF_H5FAIL;
									const char * unit_string = NULL;
									CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
									CBF_CALL(cbf_H5Aread_string(units,&unit_string));
									CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
									free((void*)unit_string);
									cbf_H5Afree(units);
								}
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"layer_thickness"));
								/* write the data */
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"threshold_energy")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								double value = 0., factor = 0./0.;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								if (CBF_SUCCESS==error) {
									/* convert the data to the correct units */
									hid_t units = CBF_H5FAIL;
									const char * unit_string = NULL;
									CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
									CBF_CALL(cbf_H5Aread_string(units,&unit_string));
									CBF_CALL(cbf_scale_units(unit_string,"eV",&factor));
									free((void*)unit_string);
									cbf_H5Afree(units);
								}
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"threshold"));
								/* write the data */
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"type")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_detector(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"detector"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"undefined_value")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									int value = 0;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_INT));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"undefined_value"));
									/* write the data */
									CBF_CALL(cbf_set_integervalue(cbf,value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"x_pixel_offset") || !strcmp(name,"y_pixel_offset") || !strcmp(name,"x_pixel_size") || !strcmp(name,"y_pixel_size")) {
						int indent = table->indent;
						if (nx->logfile) {
							while (indent--) fputc('\t',nx->logfile);
							fprintf(nx->logfile,"- %s\n",name);
						}
						/*--------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error: whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
						if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__monochromator_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"description")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"monochromator"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
		}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error: whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
						if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/*-----------------------------------------------------------------------------------------------*/
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__source_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"current")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"mA",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"current"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
		}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"name")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"type"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"power")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"kW",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"power"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"probe")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"probe"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"target_material")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"target"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"type")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"source"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"voltage")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"kV",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_source(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"voltage"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error: whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
						if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/*-----------------------------------------------------------------------------------------------*/
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__goniometer_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"description")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"device_details"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
		}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"details")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"details"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"local_name")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"device"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"type")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"device_type"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error: whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
						if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__instrument_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (0) {
						/* I don't actually have any items to match here */
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
		}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error:  whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
                        if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
                        } else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXdetector")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_detector(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__detector_op,op_data)<0) {
									cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								} else {
									/* success: extract some data that should have been returned via the op_data argument */
									if (!table->has_offset) {
										CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
										CBF_CALL(cbf_require_column(cbf,"offset"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",0.0));
									}
									if (!table->has_scaling_factor) {
										CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
										CBF_CALL(cbf_require_column(cbf,"scaling"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",1.0));
									}
									CBF_CALL(_cbf_nx2cbf_table__array_intensities(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"linearity"));
									CBF_CALL(cbf_set_value(cbf,"scaling_offset"));
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else if (!strcmp(NX_class,"NXgoniometer")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_goniometer(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__goniometer_op,op_data)<0) {
                                    cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else if (!strcmp(NX_class,"NXmonochromator")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_monochromator(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__monochromator_op,op_data)<0) {
                                    cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else if (!strcmp(NX_class,"NXsource")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_source(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__source_op,op_data)<0) {
                                    cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__beam_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
        
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				double sigma_x = 0.0, sigma_y = 0.0;
				int have_sigma_x = 0, have_sigma_y = 0;
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"beam_size_x")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* store data for later conversion */
								sigma_x = value*factor;
								have_sigma_x = 1;
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
	}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"beam_size_y")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* store data for later conversion */
								sigma_y = value*factor;
								have_sigma_y = 1;
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"collimation")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"collimation"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_divergence_x")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"degrees",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"div_x_source"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_divergence_xy")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"degrees^2",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"div_x_y_source"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_divergence_y")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								hid_t units = CBF_H5FAIL;
								double value = 0., factor = 0./0.;
								const char * unit_string = NULL;
								CBF_CALL(cbf_H5Dread2(object,0,0,0,&value,H5T_NATIVE_DOUBLE));
								CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
								CBF_CALL(cbf_H5Aread_string(units,&unit_string));
								CBF_CALL(cbf_scale_units(unit_string,"degrees",&factor));
								free((void*)unit_string);
								cbf_H5Afree(units);
								/* ensure I have suitable structure within the CBF file & write the data */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"div_y_source"));
								CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_polarisation_stokes")
                               ||!strcmp(name,"incident_polarisation_stokes_average")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (2==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[2];
								if (2!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0]) || !(4==dim[1])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0, 0};
									hsize_t count[] = {1, 4};
									double value[4] = {0., 0., 0., 0.};
									/* read the value */
									if (CBF_SUCCESS!=(error|=cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE))) {
										cbf_debug_print(cbf_strerror(error));
									} else {
										const double psn = atan2(value[2],value[1])*22.5/atan2(1.,1.);
										const double psr = sqrt(value[1]*value[1]+value[2]*value[2])/
                                        fabs(value[0]);
										/* extract & store the 2-parameter representation */
										CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
										CBF_CALL(cbf_require_column(cbf,"polarizn_source_norm_McStas"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",psn));
										CBF_CALL(cbf_require_column(cbf,"polarizn_source_ratio"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",psr));
										/*
										Store the stokes vector - assuming uniform values over all frames.
										This should only be done if the polarisation really is the same
										for all frames, if it isn't then these fields should not be used.
										There is currently no check that values are uniform across frames.
                                         
                                        At this stage we have the vector in the MCStas coordinate
                                         frame.
										*/
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_I"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value[0]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_Q_McStas"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value[1]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_U_McStas"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value[2]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_V"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value[3]));
										/* TODO: define and then store per-frame data about the radiation
                                           and rotate the stokes vector into the CBF coordimate frame */
									}
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_polarisation_stokes_uncertainties")
                               ||!strcmp(name,"incident_polarisation_stokes_average_uncertainties")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (2==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[2];
								if (2!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0]) || !(4==dim[1])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0, 0};
									hsize_t count[] = {1, 4};
									double value_esds[4] = {0., 0., 0., 0.};
									/* read the value */
									if (CBF_SUCCESS!=(error|=cbf_H5Dread2(object,offset,0,count,&value_esds,H5T_NATIVE_DOUBLE))) {
										cbf_debug_print(cbf_strerror(error));
									} else {
                                         /* Store the stokes vector esds - assuming uniform values over all frames.
                                         This should only be done if the polarisation really is the same
                                         for all frames, if it isn't then these fields should not be used.
                                         There is currently no check that values are uniform across frames.
                                             
                                         At this stage we have the uncertainties in the MCStas coordinate
                                         frame.
                                         */
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_I_esd"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value_esds[0]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_Q_McStas_esd"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value_esds[1]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_U_McStas_esd"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value_esds[2]));
										CBF_CALL(cbf_require_column(cbf,"polarizn_Stokes_V_esd"));
										CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value_esds[3]));
										/* TODO: define and then store per-frame data about the radiation
                                           rotate to the CBF coordinate frame, and generate the
                                           uncertainties for the 2-parameters form.
                                         */
									}
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"incident_wavelength")||!strcmp(name,"wavelength")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0;
									double factor;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									if (CBF_SUCCESS==error) {
										/* convert the data to the correct units */
										hid_t units = CBF_H5FAIL;
										const char * unit_string = NULL;
										CBF_CALL(cbf_H5Afind(object,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(units,&unit_string));
										CBF_CALL(cbf_scale_units(unit_string,"angstroms",&factor));
										free((void*)unit_string);
										cbf_H5Afree(units);
									}
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation_wavelength(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"wavelength"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",factor*value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"weight")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (1==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[1];
								if (1!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (!(1==dim[0] || table->frames==dim[0])) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_SIZE;
								} else {
									hsize_t offset[] = {dim[0]>1 ? nx->slice : 0};
									hsize_t count[] = {1};
									double value = 0;
									/* read the value */
									CBF_CALL(cbf_H5Dread2(object,offset,0,count,&value,H5T_NATIVE_DOUBLE));
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation_wavelength(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"wt"));
									/* write the data */
									CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",value));
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error:  whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
                        if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
                        } else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
				if (CBF_SUCCESS==error) {
					if (have_sigma_x && have_sigma_y) {
						const double inhomogeneity = (sigma_x + sigma_y) * 0.5;
						/* TODO: warn user if data may be lost due to unequal sigma_x & sigma_y: needs a comparison */
						/* ensure I have suitable structure within the CBF file & write the data */
						CBF_CALL(_cbf_nx2cbf_table__diffrn_radiation(cbf,nx,table));
						CBF_CALL(cbf_require_column(cbf,"inhomogeneity"));
						CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",inhomogeneity));
					}
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__sample_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;

		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"depends_on")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * path = NULL;
								cbf_axisData_t * prevAxisPtr = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&path));
								while (CBF_SUCCESS==error && path && strcmp(path,".")) {
									/*
                                     Given the path to an axis dataset, I want to extract
                                     all relevant details and write them out to the CBF file.
                                     */
									hid_t axis = CBF_H5FAIL;
									if (!cbf_H5Ivalid(axis=H5Dopen2(g_id, path, H5P_DEFAULT))) {
										cbf_debug_print("couldn't open dataset");
										error |= CBF_H5ERROR;
									} else {
										const char * _path = NULL;
										hid_t depends_on = CBF_H5FAIL;
										cbf_axisData_t * axisPtr = NULL;
										const char * const chr = strrchr(path,'/');
										const char * const name = NULL==chr ? path : 1+chr;
										CBF_CALL(_cbf_nx2cbf_key_require_axis(table,&axisPtr,axis,name,axisEquipment_goniometer));
                                        if (!prevAxisPtr) axisPtr->flags=CBF_AXIS_DATA_PGA;
										CBF_CALL(cbf_H5Afind(axis,&depends_on,"depends_on",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(depends_on,&_path));
										if (CBF_SUCCESS==error) {
											/* set dependency of previous axis */
											if (prevAxisPtr) prevAxisPtr->depends_on = axisPtr;
											/* some axes are shared with other peices of equipment, set the type appropriately */
											if (axisEquipment_goniometer!=axisPtr->equipment) axisPtr->equipment = axisEquipment_general;
										} else {
											cbf_H5Dfree(axis);
										}
										/* housekeeping: update the previous axis and path */
										prevAxisPtr = axisPtr;
										free((void*)path);
										path = _path;
										/* ensure hdf5 stuff is closed */
										cbf_H5Afree(depends_on);
									}
								}
								free((void*)path);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error:  whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
                        if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
                        } else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXbeam")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* leave ownership of the group with the iteration function, and process it */
							++table->indent;
							if (H5Literate(object,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__beam_op,op_data)<0) {
                                cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
								error |= CBF_H5ERROR;
							}
							table->indent = indent;
							/*-----------------------------------------------------------------------------------------------*/
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

	static int cbf_write_nx2cbf__entry_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;

		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			const op_data_t * const op_data_struct = op_data;
			cbf_h5handle nx = op_data_struct->nx;
			cbf_handle cbf = op_data_struct->cbf;
			cbf_nx2cbf_key_t * const table = op_data_struct->table;
			hid_t object = CBF_H5FAIL;
			H5I_type_t type = H5I_BADID;
			if (!nx) {
				cbf_debug_print("Invalid NeXus handle given");
				error |= CBF_ARGUMENT;
			} else if (!cbf) {
				cbf_debug_print("No CBF handle given");
				error |= CBF_ARGUMENT;
			} else if (!table) {
				cbf_debug_print("No key given");
				error |= CBF_ARGUMENT;
			} else if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
				cbf_debug_print2("error: couldn't open '%s'\n",name);
				error |= CBF_H5ERROR;
			} else if (H5I_BADID==(type=H5Iget_type(object))) {
				cbf_debug_print2("error: couldn't get type of '%s'\n",name);
				error |= CBF_H5ERROR;
			} else {
				if (H5I_BADID==type) {
					/* something went wrong when finding the object type */
					cbf_debug_print2("error: couldn't get object type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_DATASET==type) {
					/* handle all datasets here */
					if (!strcmp(name,"end_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_scan(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"date_end"));
								/* write the data */
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
		}
		}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"method")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								CBF_CALL(_cbf_nx2cbf_table__diffrn_measurement(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"method"));
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
		}
						}
						cbf_H5Sfree(data_space);
						/*-----------------------------------------------------------------------------------------------*/
					} else if (!strcmp(name,"start_time")) {
						hid_t data_space = CBF_H5FAIL;
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,1);
						if (!cbf_H5Ivalid(data_space=H5Dget_space(object))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else {
							/* check rank, allowing for multiple usable results */
							if (0==H5Sget_simple_extent_ndims(data_space)) {
								const char * value = NULL;
								CBF_CALL(_cbf_nx2cbfDread_scalar_string(object,&value));
								/* ensure I have suitable structure within the CBF file */
								CBF_CALL(_cbf_nx2cbf_table__diffrn_scan(cbf,nx,table));
								CBF_CALL(cbf_require_column(cbf,"date_start"));
								/* write the data */
								CBF_CALL(cbf_set_value(cbf,value));
								free((void*)value);
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						/*--------------------------------------------------------------------------------------*/
					} else {
						/* unknown field: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					}
				} else if (H5I_GROUP==type) {
					/* get NXclass & handle all groups here */
					const char * NX_class = NULL;
					const int found = _cbf_NXclass(object,&NX_class);
					if (CBF_NOTFOUND==found) {
						/* no NX_class: can't process it, but it's not an error */
						if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
					} else if (CBF_SUCCESS!=found) {
						if (1) {
							cbf_debug_print(cbf_strerror(found));
							cbf_debug_print2("error:  whilst processing group '%s'\n",name);
						}
						error |= found;
					} else {
						/* I have a group with an NX_class: match on NX_class */
                        if (!strcmp(NX_class,"NXtransformations")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
                        } else if (!strcmp(NX_class,"NXpoise")) {
							/* known class that will be processed */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXcollection") || !strcmp(NX_class,"NXdata")) {
							/* known class that should be ignored: ignoring it is the correct way to process it */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
						} else if (!strcmp(NX_class,"NXinstrument")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_instrument(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__instrument_op,op_data)<0) {
                                    cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else if (!strcmp(NX_class,"NXsample")) {
							const unsigned int indent = table->indent;
							hsize_t idx = 0;
							hid_t group = object;
							/* debugging output */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,1);
							/* try to take ownership of the group away from the iteration function */
							if (CBF_SUCCESS!=(error|=cbf_h5handle_set_sample(nx,object,name))) {
								if (1) {
									cbf_debug_print(cbf_strerror(found));
									cbf_debug_print2("error:  failed to set the '%s' group in the handle\n",name);
								}
							} else {
								object = CBF_H5FAIL;
								/* The hdf5 handle now owns the group, process it */
								++table->indent;
								if (H5Literate(group,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__sample_op,op_data)<0) {
                                    cbf_debug_print3("error: failed to iterate over items in the '%s:%s' group\n",name,NX_class);
									error |= CBF_H5ERROR;
								}
								table->indent = indent;
							}
							/*-----------------------------------------------------------------------------------------------*/
						} else {
							/* unknown NX_class: (probably) not an error */
							if (nx->logfile) _cbf_write_name(nx->logfile,name,NX_class,table->indent,0);
						}
					}
					free((void*)NX_class);
				} else {
					/* unrecognised object type: can't process it, but it's not an error */
					if (nx->logfile) _cbf_write_name(nx->logfile,name,0,table->indent,0);
				}
			}
			if (cbf_H5Ivalid(object)) H5Oclose(object);
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? 0 : -1;
	}

    /* sorting function for categories */
	static int cmp_category
    (const void * const p1,
     const void * const p2)
	{
		const char last[] = "array_data";
		const cbf_node * const * const n1 = p1;
		const cbf_node * const * const n2 = p2;
		const char * const s1 = (*n1)->name;
		const char * const s2 = (*n2)->name;
		if (!strcmp(s1,s2)) return 0;
		else return (!strcmp(s1,last) || (strcmp(s2,last) && strcmp(s1,s2)>0)) ? 1 : -1;
	}

	/* sorting function for columns */
	static int cmp_column
    (const void * const p1,
     const void * const p2)
	{
		const char str[] = "id";
		const cbf_node * const * const n1 = p1;
		const cbf_node * const * const n2 = p2;
		const char * const s1 = (*n1)->name;
		const char * const s2 = (*n2)->name;
		const int cmp = strcmp(s1,s2);
		/* do the comparison: first check for equality, then for important values, then order the rest */
		if (!cmp) return 0;
		else if (!strcmp(str,s1)) return -1;
		else if (!strcmp(str,s2)) return +1;
		else return cmp;
	}

	/* sorting function for 'array_data' category */
	static int cmp_arraydata
    (const void * const p1,
     const void * const p2)
	{
		const char str[] = "data";
		const cbf_node * const * const n1 = p1;
		const cbf_node * const * const n2 = p2;
		const char * const s1 = (*n1)->name;
		const char * const s2 = (*n2)->name;
		const int cmp = strcmp(s1,s2);
		/* do the comparison: first check for equality, then for important values, then order the rest */
		if (!cmp) return 0;
		else if (!strcmp(str,s1)) return +1;
		else if (!strcmp(str,s2)) return -1;
		else return cmp;
		}

	typedef struct cbf_H5_findObject_t
	{
		hid_t * foundField; /*< Where to store the object that was found. */
		const char * * foundName; /*< Where to store the name of the object that was found. */
		const char * searchName; /*< The name of the object, or NULL for any field name. */
		const char * searchClass; /*< The 'NX_class' of the object, or NULL for any class. */
		H5I_type_t searchType; /*< The HDF5 type of the object (see: H5Iget_type), or 'H5I_BADID' for any type. */
	} cbf_H5_findObject_t;
    
	/*
     Given an instance of 'cbf_H5_findObject_t' as the 'op_data', find a matching object and return
     both the object and its name. The name should later be free'd by the caller.
     
     If a match is found at a given level then a positive value should be returned. If an error occurs
     then a negative value should be returned. Failure to find a match will result in a return value
     of 0 (unless there was an error) and the value at 'cbf_H5_findObject_t::field' being unchanged.
     */
	static int cbf_findObject_op
    (hid_t g_id,
     const char * name,
     const H5L_info_t * info,
     void * op_data)
	{
		int error = CBF_SUCCESS;
		int found = 0;
		if (!cbf_H5Ivalid(g_id) || !name || !info || !op_data) {
			cbf_debug_print(cbf_strerror(CBF_ARGUMENT));
			error |= CBF_ARGUMENT;
		} else {
			H5I_type_t type = H5I_BADID;
			cbf_H5_findObject_t * const findObject = (cbf_H5_findObject_t*) op_data;
			if (!findObject->searchName || !strcmp(name,findObject->searchName)) {
				hid_t object = CBF_H5FAIL;
				if (!cbf_H5Ivalid(object=H5Oopen(g_id, name, H5P_DEFAULT))) {
					cbf_debug_print2("error: couldn't open '%s'\n",name);
					error |= CBF_H5ERROR;
				} else if (H5I_BADID==(type=H5Iget_type(object))) {
					cbf_debug_print2("error: couldn't get type of '%s'\n",name);
					error |= CBF_H5ERROR;
				} else {
					/* check object type: */
					if (H5I_BADID==findObject->searchType || findObject->searchType==type) {
						const char * class = NULL;
						if (findObject->searchClass && CBF_SUCCESS!=(error|=_cbf_NXclass(object,&class))) {
							cbf_debug_print("couldn't get value of 'NX_class' attribute");
							cbf_debug_print(cbf_strerror(error));
		}
						/* check 'NX_class': */
						if (!findObject->searchClass || (class && !strcmp(class,findObject->searchClass))) {
							/* I have a match! */
							found = 1;
							*(findObject->foundField) = object;
							*(findObject->foundName) = _cbf_strdup(name);
							object = CBF_H5FAIL;
		}
						free((void*)class);
		}
				}
				if (cbf_H5Ivalid(object)) H5Oclose(object);
			}
		}
		/*
         Convert a CBF error to something the HDF5 iteration function can understand.
         All errors should already have been reported, so I shouldn't need to print anything.
         */
		return (CBF_SUCCESS==error) ? (found ? +1 : 0) : (-1);
	}

	/**
     Reads NeXus-format data from the entry group defined in the <code>nx</code> handle, extracting data
     related to the frame with index <code>nx->slice</code> and in CBF-format within the the <code>cbf</code>
     handle.
     
     \param nx The handle defining the NeXus data to be converted.
     \param cbf The handle in which to store the resulting CBF data.
     \sa cbf_write_cbf_h5file
     \sa cbf_write_minicbf_h5file
     \sa cbf_write_nx2cbf
     \return An error code.
     */
	int cbf_write_nx2cbf
    (cbf_h5handle nx,
     cbf_handle cbf)
	{
		int error = CBF_SUCCESS;
		hid_t entry = CBF_H5FAIL;
		const char * entry_name = NULL;
        
		/* check for appropriate items in the handle */
		if (!nx) {
			cbf_debug_print("No NeXus handle given\n");
			error |= CBF_ARGUMENT;
		} else if (!cbf) {
			cbf_debug_print("No CBF handle given\n");
			error |= CBF_ARGUMENT;
		} else {
			size_t _array_id_size = 0;
			char * _array_id = NULL;
			const char array_id[] = "array_1";
			const char datablock_id[] = "db_1";
			const char diffrn_id[] = "diffrn_1";
			const char diffrn_detector_id[] = "diffrn_detector_1";
			const char diffrn_detector_element_id[] = "diffrn_detector_element_1";
			const char diffrn_measurement_id[] = "diffrn_measurement_1";
			const char frame_id[] = "frame_1";
			const char scan_id[] = "scan_1";
			const char wavelength_id[] = "wavelength_1";
			cbf_nx2cbf_key_t table[1];
            
			/* initialise & populate the key */
			if (CBF_SUCCESS!=(error|=_cbf_create_nx2cbf_key(table))) {
				cbf_debug_print(cbf_strerror(error));
			} else {
				table->array_id = array_id;
				table->binary_id = 1;
				table->datablock_id = datablock_id;
				table->diffrn_id = diffrn_id;
				table->diffrn_detector_id = diffrn_detector_id;
				table->diffrn_detector_element_id = diffrn_detector_element_id;
				table->diffrn_measurement_id = diffrn_measurement_id;
				table->frame_id = frame_id;
				table->scan_id = scan_id;
				table->wavelength_id = wavelength_id;
		}

			/*
             Start by converting the data, obtaining some primary keys required for converting the rest of the data.
             When I have the data:
             - match/insert settings for a given image axis in 'axis' and 'array_structure_list_axis' categories.
             - obtain several axis_set_ids from the above step, one per image axis, which won't need to be changed.
             - match/insert a row of 'array_structure_list' for each axis_set_id.
             if all matched rows in 'array_structure_list' have the same array_id then:
             - match/insert a row in 'array_structure', duplicating the relevant rows of 'array_structure_list'
             if a new 'array_structure' row had to be added.
             else:
             - duplicate existing rows of 'array_structure_list', giving them the new array_id.
             - insert a new row into 'array_structure'.
             fi
             - use the array_id obtained above to extract the smallest permissible binary_id for an image.
             - insert the image data with the array_id & binary_id, caching them to be referred to later.
             */
			if (CBF_SUCCESS!=(error|=cbf_h5handle_get_entry(nx, &entry, &entry_name))) {
					cbf_debug_print("error: couldn't get current entry from NeXus file handle");
					cbf_debug_print(cbf_strerror(error));
		}
            if (!error && nx->logfile) {
                fputc('\n',nx->logfile);
                int len = fprintf(nx->logfile,"Extracting data from '%s:NXentry':\n",entry_name);
                while (--len > 0) fputc('=',nx->logfile);
                fputc('\n',nx->logfile);
			}
			if (CBF_SUCCESS==error) {
				const char empty[] = "";
				const char no_compression[] = "none";
				const char canonical[] = "canonical";
				const char packed[] = "packed";
				const char packed_v2[] = "packed_v2";
				const char byte_offset[] = "byte_offset";
				const char nibble_offset[] = "nibble_offset";
				const char big_endian[] = "big_endian";
				const char little_endian[] = "little_endian";
				const char * data_byte_order = NULL;
				const char * data_compression = NULL;
				char * _data_encoding = NULL;
				const char * data_encoding = empty;
				size_t _data_encoding_size = 0;
				unsigned int data_row = ~0x0;
				hid_t instrument = CBF_H5FAIL;
				hid_t detector = CBF_H5FAIL;
				hid_t data = CBF_H5FAIL;
                if (!error && nx->logfile) {
                    fputc('\n',nx->logfile);
                    int len = fprintf(nx->logfile,"Counting frames & converting data:\n");
                    while (--len > 0) fputc('-',nx->logfile);
                    fputc('\n',nx->logfile);
				}
				if (CBF_SUCCESS==error) {
					/* find instrument */
					hsize_t idx = 0;
					const char * groupName = NULL;
					const char class[] = "NXinstrument";
					cbf_H5_findObject_t find_data = {&instrument, &groupName, NULL, class, H5I_GROUP};
					const herr_t err = H5Literate(entry,H5_INDEX_NAME,H5_ITER_INC,&idx,cbf_findObject_op,&find_data);
					if (err < 0) {
						cbf_debug_print2("error: problem while trying to find '*:%s'\n",class);
						error |= CBF_H5ERROR;
					} else if (!err) {
						cbf_debug_print2("error: couldn't find '*:%s'\n",class);
						error |= CBF_NOTFOUND;
					} else {
						if (CBF_SUCCESS!=(error|=cbf_h5handle_set_instrument(nx,instrument,groupName))) {
							cbf_debug_print(cbf_strerror(error));
							cbf_H5Gfree(instrument);
						}
					}
					free((void*)groupName);
				}
				if (CBF_SUCCESS==error) {
					/* find detector */
					hsize_t idx = 0;
					const char * groupName = NULL;
					const char class[] = "NXdetector";
					cbf_H5_findObject_t find_data = {&detector, &groupName, NULL, class, H5I_GROUP};
					const herr_t err = H5Literate(instrument,H5_INDEX_NAME,H5_ITER_INC,&idx,cbf_findObject_op,&find_data);
					if (err < 0) {
						cbf_debug_print2("error: problem while trying to find '*:%s'\n",class);
						error |= CBF_H5ERROR;
					} else if (!err) {
						cbf_debug_print2("error: couldn't find '*:%s'\n",class);
						error |= CBF_NOTFOUND;
					} else {
						if (CBF_SUCCESS!=(error|=cbf_h5handle_set_detector(nx,detector,groupName))) {
							cbf_debug_print(cbf_strerror(error));
							cbf_H5Gfree(detector);
						}
					}
					free((void*)groupName);
				}
				if (CBF_SUCCESS==error) {
					/*
                     find data
                     TODO: use more direct method, instead of using the iteration function?
                     */
					hsize_t idx = 0;
					const char * groupName = NULL;
					const char name[] = "data";
					cbf_H5_findObject_t find_data = {&data, &groupName, name, NULL, H5I_DATASET};
					const herr_t err = H5Literate(detector,H5_INDEX_NAME,H5_ITER_INC,&idx,cbf_findObject_op,&find_data);
					if (err < 0) {
						cbf_debug_print2("error: problem while trying to find '%s'\n",name);
						error |= CBF_H5ERROR;
					} else if (!err) {
						cbf_debug_print2("error: couldn't find '%s'\n",name);
						error |= CBF_NOTFOUND;
					}
					free((void*)groupName);
				}
				if (CBF_SUCCESS==error) {
					/* extract dimensions of data */
					hsize_t dims[3];
					/* extract dimensions of data, convert it and get data format & layout metadata */
					hid_t data_space = CBF_H5FAIL;
					if (!cbf_H5Ivalid(data_space=H5Dget_space(data))) {
						cbf_debug_print("could not get data space");
						error |= CBF_H5ERROR;
					} else if (3!=H5Sget_simple_extent_ndims(data_space)) {
						cbf_debug_print("incorrect data rank");
						error |= CBF_H5DIFFERENT;
					} else if (3!=H5Sget_simple_extent_dims(data_space,dims,0)) {
						cbf_debug_print("could not get dimensions of data");
						error |= CBF_H5ERROR;
					} else {
						table->frames = dims[0];
						table->xdim = dims[2];
						table->ydim = dims[1];
					}
					cbf_H5Sfree(data_space);
				}
                if (!error && nx->logfile) {
                    /* tell the user something about the data if they requested some information */
                    fprintf(
                            nx->logfile,
                                     "Found %zu frame%s\nframe dimensions: [%zu, %zu]\n",
                                     (size_t)(table->frames),
                                     table->frames != 1 ? "s" : "",
                                     (size_t)(table->ydim),
                                     (size_t)(table->xdim)
                                     );
                    fprintf(nx->logfile,"%zu elems per frame\n",(size_t)(table->xdim*table->ydim));
				}
				if (CBF_SUCCESS==error) {
					/* log image axes for later use */
					const char x_pixel_offset[] = "x_pixel_offset";
					const char y_pixel_offset[] = "y_pixel_offset";
					const char x_pixel_size[] = "x_pixel_size";
					const char y_pixel_size[] = "y_pixel_size";
					const char * pixel_offset_name[] = {y_pixel_offset,x_pixel_offset};
					const char * pixel_size_name[] = {y_pixel_size,x_pixel_size};
					const char * _axis_set_id[] = {NULL, NULL}; /*< always free'able */
					const char * axis_set_id[] = {empty, empty}; /*< always useable */
					const hsize_t pixel_offset_dim[] = {table->ydim,table->xdim};
					double elem_size[] = {0./0., 0./0.};
					int i;
					for (i = 0; i != 2; ++i) {
						hid_t pixel_data = CBF_H5FAIL;
						hid_t data_space = CBF_H5FAIL;
						const char * path = _cbf_strdup(pixel_offset_name[i]);
						double disp = 0.; /*< read from '*:NXdetector/[xy]_pixel_offset' */
						double disp_incr = 0.; /*< read from '*:NXdetector/[xy]_pixel_size' */
						int sign = 0;
						/* extract pixel offset data */
						if (!cbf_H5Ivalid(pixel_data=H5Dopen2(detector,pixel_offset_name[i],H5P_DEFAULT))) {
							cbf_debug_print("error: couldn't open a dataset");
							error |= CBF_H5ERROR;
						} else if (!cbf_H5Ivalid(data_space=H5Dget_space(pixel_data))) {
							cbf_debug_print("error: couldn't get a dataspace");
							error |= CBF_H5ERROR;
						} else {
							const int rank = H5Sget_simple_extent_ndims(data_space);
							if (rank < 0) {
								cbf_debug_print("error: problem getting the rank of a dataset");
								error |= CBF_H5ERROR;
							} else if (1==rank) {
								hsize_t dims[1];
								if (rank != H5Sget_simple_extent_dims(data_space,dims,0)) {
									cbf_debug_print("error: problem getting the dimensions of a dataset");
									error |= CBF_H5ERROR;
								} else if (dims[0] != pixel_offset_dim[i]) {
									cbf_debug_print("error: dimensions of pixel offset don't match dimensions of data");
									error |= CBF_H5DIFFERENT;
								} else {
									/*
                                     I (probably) have a suitable axis:
                                     - extract the first number to store as 'array_structure_list_axis.displacement'
                                     - assume that it's a uniformly spaced array of pixels in 3D space, so ignore subsequent values
                                     - store it (and dependency chain) in the key, to be converted along with other axes
                                     */
									const hsize_t off[] = {0};
									const hsize_t cnt[] = {2};
									double disp2[] = {0.,0.};
									double factor = 0./0.;
									/* extract data */
									CBF_CALL(cbf_H5Dread2(pixel_data,off,NULL,cnt,disp2,H5T_NATIVE_DOUBLE));
									if (CBF_SUCCESS==error) {
										/* convert the data to the correct units */
										hid_t units = CBF_H5FAIL;
										const char * unit_string = NULL;
										CBF_CALL(cbf_H5Afind(pixel_data,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
										CBF_CALL(cbf_H5Aread_string(units,&unit_string));
                                        CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
										free((void*)unit_string);
										cbf_H5Afree(units);
									}
									disp = disp2[0]*factor;
									sign = (disp2[1]-disp2[0]) >= 0. ? +1 : -1;
								}
							} else {
								cbf_debug_print("error: unsupported rank of a 'pixel_offset' field");
								error |= CBF_NOTIMPLEMENTED;
							}
						}
						cbf_H5Sfree(data_space);
						cbf_H5Dfree(pixel_data);
						pixel_data = CBF_H5FAIL;
						data_space = CBF_H5FAIL;
						/*
                         Extract pixel size data.
                         TODO: make the presence of this data optional, using the pixel_offset fields as a backup option.
                         */
						if (!cbf_H5Ivalid(pixel_data=H5Dopen2(detector,pixel_size_name[i],H5P_DEFAULT))) {
							cbf_debug_print("error: couldn't open a dataset");
							error |= CBF_H5ERROR;
						} else if (!cbf_H5Ivalid(data_space=H5Dget_space(pixel_data))) {
							cbf_debug_print("error: couldn't get a dataspace");
							error |= CBF_H5ERROR;
						} else {
							const int rank = H5Sget_simple_extent_ndims(data_space);
							if (rank < 0) {
								cbf_debug_print("error: problem getting the rank of a dataset");
								error |= CBF_H5ERROR;
							} else if (0==rank) {
								double size = 0.;
								double factor = 0./0.;
								CBF_CALL(cbf_H5Dread2(pixel_data,NULL,NULL,NULL,&size,H5T_NATIVE_DOUBLE));
								if (CBF_SUCCESS==error) {
									/* convert the data to the correct units */
									hid_t units = CBF_H5FAIL;
									const char * unit_string = NULL;
									CBF_CALL(cbf_H5Afind(pixel_data,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
									CBF_CALL(cbf_H5Aread_string(units,&unit_string));
                                    CBF_CALL(cbf_scale_units(unit_string,"mm",&factor));
									free((void*)unit_string);
									cbf_H5Afree(units);
								}
								disp_incr = fabs(size)*factor*sign;
								elem_size[i] = fabs(size)*factor*.001;
							} else {
								/* pixel size is (possibly) not uniform, this can't be handled in CBF -> fail */
								cbf_debug_print("error: unsupported rank of a 'pixel_offset' field");
								error |= CBF_FORMAT;
							}
						}
						cbf_H5Sfree(data_space);
						cbf_H5Dfree(pixel_data);
						if (CBF_SUCCESS==error) {
							cbf_axisData_t * prevAxisPtr = NULL;
							while (CBF_SUCCESS==error && path && strcmp(path,".")) {
								/*
                                 Given the path to an axis dataset, I want to extract
                                 all relevant details and write them out to the CBF file.
                                 */
								hid_t axis = CBF_H5FAIL;
								if (!cbf_H5Ivalid(axis=H5Dopen2(detector, path, H5P_DEFAULT))) {
									cbf_debug_print("couldn't open dataset");
									error |= CBF_H5ERROR;
								} else {
									const char * _path = NULL;
									hid_t depends_on = CBF_H5FAIL;
									cbf_axisData_t * axisPtr = NULL;
									const char * const chr = strrchr(path,'/');
									const char * const name = NULL==chr ? path : 1+chr;
									CBF_CALL(_cbf_nx2cbf_key_require_axis(table,&axisPtr,axis,name,axisEquipment_image));
									CBF_CALL(cbf_H5Afind(axis,&depends_on,"depends_on",CBF_H5FAIL,CBF_H5FAIL));
									CBF_CALL(cbf_H5Aread_string(depends_on,&_path));
									if (CBF_SUCCESS==error) {
                                        /* set dependency of previous axis */
										if (prevAxisPtr) prevAxisPtr->depends_on = axisPtr;
										/* some axes are shared with other peices of equipment, set the type appropriately */
										if (axisEquipment_image!=axisPtr->equipment && axisEquipment_detector!=axisPtr->equipment) {
											axisPtr->equipment = axisEquipment_general;
										}
									} else {
										cbf_H5Dfree(axis);
									}
									/* housekeeping: update the previous axis and path */
									prevAxisPtr = axisPtr;
									free((void*)path);
									path = _path;
									/* ensure hdf5 stuff is closed */
									cbf_H5Afree(depends_on);
								}
							}
						}
						free((void*)path);
						if (CBF_SUCCESS==error) {
							/* search for all rows in 'array_structure_list_axis' with matching axis_id, get a unique axis_set_id to store */
							unsigned int * rows = NULL;
							cbf_node * node = NULL;
							unsigned int j, nRows = 0;
							/* select/insert a column in the CBF file */
							CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
							/* TODO: add a function to ensure all foreign keys exist? */
							CBF_CALL(cbf_require_category(cbf,"array_structure_list_axis"));
							CBF_CALL(cbf_require_column(cbf,"axis_id"));
							node = cbf->node;
							/* extract a node set of rows with matching axis_ids from the CBF file */
							rows = malloc(node->children*sizeof(unsigned int));
							for (j = 0; CBF_SUCCESS==error && j != node->children; ++j) {
								const char * val = NULL;
								CBF_CALL(cbf_node_get_value(node,j,&val));
								if (val && !strcmp(val,pixel_offset_name[i])) rows[nRows++] = j;
							}
							if (0==nRows) {
								/* axis name is not yet present, no suffix needed */
								CBF_CALL(cbf_new_row(cbf));
								CBF_CALL(cbf_set_value(cbf,pixel_offset_name[i]));
								CBF_CALL(cbf_require_column(cbf,"axis_set_id"));
								axis_set_id[i] = pixel_offset_name[i];
								CBF_CALL(cbf_set_value(cbf,axis_set_id[i]));
								CBF_CALL(cbf_require_column(cbf,"displacement"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",disp));
								CBF_CALL(cbf_require_column(cbf,"displacement_increment"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",disp_incr));
							} else {
								/*
                                 The node set is indexed by rows[0:nRows], generate a unique axis_set_id using the axis name
                                 and a numeric suffix. Store the generated string in '_axis_set_id', and point 'axis_set_id'
                                 towards it.
                                 */
								cbf_debug_print("generation of unique 'axis_set_id's is not yet implemented");
								error |= CBF_NOTIMPLEMENTED;
							}
							free((void*)rows);
						}
					}
					/*
                     I have axis_set_ids to use, I need a matching or new array_id. Simplest solution is one array_id per
                     stack of frames added to the file, with a new id generated each time this function is run.
                     */
					if (CBF_SUCCESS==error) {
						cbf_node * node = NULL;
						unsigned int id = 0;
						CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
						CBF_CALL(cbf_require_category(cbf,"array_structure"));
						CBF_CALL(cbf_require_column(cbf,"id"));
						node = cbf->node;
						/* iteratively attempt to find an id that isn't used via a template like "array_%u" */
						while (CBF_SUCCESS==error) {
							int found = CBF_SUCCESS;
							/* generate a test id */
							while (CBF_SUCCESS==error) {
								char * _array_id_new = NULL;
								const int n = snprintf(_array_id,_array_id_size,"array_%u",id);
								/* check if the string was formed successfully */
								if (n > -1 && n < _array_id_size) break;
								/* otherwise, set its size to the correct size or to the next higher power-of-2 */
								if (n > -1) _array_id_size = 1+n;
								else _array_id_size = _array_id_size ? 2*_array_id_size : 1;
								/* reallocate the string */
								if (NULL==(_array_id_new=realloc(_array_id,_array_id_size))) error |= CBF_ALLOC;
								else _array_id = _array_id_new;
							}
							/* search for it in the list of existing ids */
							found = cbf_find_row(cbf,_array_id);
							if (CBF_NOTFOUND==found) {
								table->array_id = _array_id;
								break;
							} else if (CBF_SUCCESS!=found) {
								cbf_debug_print(cbf_strerror(found));
								error |= found;
							}
							/* it already exists, try the next one... */
							++id;
						}
					}
					/* I have an array_id, I need to generate a unique binary id to accompany it */
					if (CBF_SUCCESS==error) {
						/* TODO */
					}
					/* write the data & extract some metadata from it */
					if (CBF_SUCCESS==error) {
						hid_t data_space = CBF_H5FAIL;
						hid_t data_type = CBF_H5FAIL;
						if (!cbf_H5Ivalid(data_space=H5Dget_space(data))) {
							cbf_debug_print("could not get data space");
							error |= CBF_H5ERROR;
						} else if (!cbf_H5Ivalid(data_type=H5Dget_type(data))) {
							cbf_debug_print("could not get data type");
							error |= CBF_H5ERROR;
						} else {
							/* check rank of data, allowing for multiple usable results */
							if (3==H5Sget_simple_extent_ndims(data_space)) {
								hsize_t dim[3];
								if (3!=H5Sget_simple_extent_dims(data_space,dim,0)) {
									cbf_debug_print("Couldn't get dimensions of dataset");
									error |= CBF_H5ERROR;
								} else if (table->frames!=dim[0] || table->ydim!=dim[1] || table->xdim!=dim[2]) {
									cbf_debug_print("invalid dimensions of dataset");
									error |= CBF_H5DIFFERENT;
								} else {
									hid_t native_type = CBF_H5FAIL;
									/* ensure I have suitable structure within the CBF file */
									CBF_CALL(_cbf_nx2cbf_table__array_data(cbf,nx,table));
									CBF_CALL(cbf_require_column(cbf,"data"));
									data_row = cbf->row;
									/* extract the data */
									if (!cbf_H5Ivalid(native_type=H5Tget_native_type(data_type,H5T_DIR_ASCEND))) {
										cbf_debug_print("Couldn't get native type of dataset");
										error |= CBF_H5ERROR;
									} else if (H5Tequal(native_type,H5T_NATIVE_INT) || H5Tequal(native_type,H5T_NATIVE_UINT) /* etc. */) {
										/* extract the data from HDF5 and store in CBF */
										{
											hsize_t offset[] = {nx->slice,0,0};
											hsize_t count[] = {1,dim[1],dim[2]};
											unsigned int compression = CBF_BYTE_OFFSET;
											const H5T_sign_t h5sign = H5Tget_sign(native_type);
											const size_t nelems = count[0]*count[1]*count[2];
											const size_t elem_size = H5Tget_size(native_type);
											void * const array = malloc(nelems*elem_size);
											const H5T_order_t h5order = H5Tget_order(native_type);
											if (H5T_ORDER_LE==h5order) data_byte_order = little_endian;
											else if (H5T_ORDER_BE==h5order) data_byte_order = big_endian;
											/* extract data from HDF5 and store in CBF: */
											if (h5sign<0) {
												cbf_debug_print("Couldn't get sign of integer datatype");
												error |= CBF_H5ERROR;
											}
											CBF_CALL(cbf_H5Dread2(data,offset,0,count,array,native_type));
											CBF_CALL(
                                                     cbf_set_integerarray_wdims(
                                                                                cbf,
                                                                                compression,
                                                                                table->binary_id,
                                                                                array,
                                                                                elem_size,
                                                                                H5T_SGN_2==h5sign ? 1 : 0,
                                                                                nelems,
                                                                                data_byte_order,
                                                                                count[2],
                                                                                count[1],
                                                                                count[0],
                                                                                0
                                                                                )
                                                     );
											free((void*)array);
											/* map the compression to its string */
											switch (compression) {
												case CBF_CANONICAL: {data_compression = canonical; break;}
												case CBF_PACKED: {data_compression = packed; break;}
												case CBF_PACKED_V2: {data_compression = packed_v2; break;}
												case CBF_BYTE_OFFSET: {data_compression = byte_offset; break;}
												case CBF_NIBBLE_OFFSET: {data_compression = nibble_offset; break;}
												default: {data_compression = no_compression;}
											}
											/* generate the encoding string */
											while (CBF_SUCCESS==error) {
												char * _data_encoding_new = NULL;
												const int n = snprintf(
                                                                       _data_encoding,
                                                                       _data_encoding_size,
                                                                       "%ssigned %zu-bit integer",
                                                                       H5T_SGN_2==h5sign?"":"un",
                                                                       8*elem_size
                                                                       );
												/* check if the string was formed successfully */
												if (n > -1 && n < _data_encoding_size) break;
												/* otherwise, set its size to the correct size or to the next higher power-of-2 */
												if (n > -1) _data_encoding_size = 1+n;
												else _data_encoding_size = _data_encoding_size ? 2*_data_encoding_size : 1;
												/* reallocate the string */
												if (NULL==(_data_encoding_new=realloc(_data_encoding,_data_encoding_size))) {
													error |= CBF_ALLOC;
												} else {
													_data_encoding = _data_encoding_new;
												}
											}
											data_encoding = _data_encoding;
											/* debugging */
                                            if (!error && nx->logfile) {
                                                fprintf(nx->logfile,"CBF compression: '%s'\n",data_compression);
                                                fprintf(nx->logfile,"byte_order: '%s'\n",data_byte_order);
                                                fprintf(nx->logfile,"encoding: '%s'\n",data_encoding);
											}
										}
									} else if (H5Tequal(native_type,H5T_NATIVE_FLOAT) || H5Tequal(native_type,H5T_NATIVE_DOUBLE)) {
										/* TODO: other data types */
										cbf_debug_print("Floating-point datasets not currently supported");
										error |= CBF_NOTIMPLEMENTED;
									} else {
										cbf_debug_print("Unsupported native type of dataset");
										error |= CBF_NOTIMPLEMENTED;
									}
									cbf_H5Tfree(native_type);
								}
							} else {
								cbf_debug_print("incorrect data rank");
								error |= CBF_H5DIFFERENT;
							}
						}
						cbf_H5Sfree(data_space);
						cbf_H5Tfree(data_type);
					}
					/* write metadata about the data */
					if (CBF_SUCCESS==error) {
						size_t dimension[] = {table->ydim,table->xdim};
						const int precedence[] = {2,1};
						CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
						/* array_structure category */
						CBF_CALL(cbf_require_category(cbf,"array_structure"));
						CBF_CALL(cbf_require_column(cbf,"id"));
						CBF_CALL(cbf_new_row(cbf));
						CBF_CALL(cbf_set_value(cbf,table->array_id));
						CBF_CALL(cbf_require_column(cbf,"byte_order"));
						CBF_CALL(cbf_set_value(cbf,data_byte_order));
						CBF_CALL(cbf_require_column(cbf,"compression_type"));
						CBF_CALL(cbf_set_value(cbf,data_compression));
						CBF_CALL(cbf_require_column(cbf,"encoding_type"));
						CBF_CALL(cbf_set_value(cbf,data_encoding));
						/* array_structure_list category */
						CBF_CALL(cbf_require_category(cbf,"array_structure_list"));
						for (i = 0; CBF_SUCCESS==error && i != 2; ++i) {
							CBF_CALL(cbf_require_column(cbf,"array_id"));
							CBF_CALL(cbf_new_row(cbf));
							CBF_CALL(cbf_set_value(cbf,table->array_id));
							CBF_CALL(cbf_require_column(cbf,"axis_set_id"));
							CBF_CALL(cbf_set_value(cbf,axis_set_id[i]));
							CBF_CALL(cbf_require_column(cbf,"dimension"));
							CBF_CALL(cbf_set_integervalue(cbf,dimension[i]));
							CBF_CALL(cbf_require_column(cbf,"direction"));
							CBF_CALL(cbf_set_value(cbf,"increasing"));
							/* TODO: check the index & precedence are correct */
							CBF_CALL(cbf_require_column(cbf,"index"));
							CBF_CALL(cbf_set_integervalue(cbf,precedence[i]));
							CBF_CALL(cbf_require_column(cbf,"precedence"));
							CBF_CALL(cbf_set_integervalue(cbf,precedence[i]));
						}
					}
					if (CBF_SUCCESS==error) {
						const int precedence[] = {2,1};
						CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
						CBF_CALL(cbf_require_category(cbf,"array_element_size"));
						for (i = 0; i != 2; ++i) {
							CBF_CALL(cbf_require_column(cbf,"array_id"));
							CBF_CALL(cbf_new_row(cbf));
							CBF_CALL(cbf_set_value(cbf,table->array_id));
							CBF_CALL(cbf_require_column(cbf,"index"));
							CBF_CALL(cbf_set_integervalue(cbf,precedence[i]));
							CBF_CALL(cbf_require_column(cbf,"size"));
                            CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",elem_size[i]));
						}
					}
					free((void*)_axis_set_id[0]);
					free((void*)_axis_set_id[1]);
				}
				cbf_H5Dfree(data);
				free((void*)_data_encoding);
			}

			/*
             Do the conversion of metadata in the file.
             */
			if (CBF_SUCCESS==error) {
				hsize_t idx = 0;
				op_data_t op_data_struct = {nx, cbf, table};
                if (!error && nx->logfile) {
                    fputc('\n',nx->logfile);
                    int len = fprintf(nx->logfile,"Converting metadata:\n");
                    while (--len > 0) fputc('-',nx->logfile);
                    fputc('\n',nx->logfile);
		}
				if (H5Literate(entry,H5_INDEX_NAME,H5_ITER_NATIVE,&idx,cbf_write_nx2cbf__entry_op,&op_data_struct)<0) {
					cbf_debug_print2("error: failed to iterate over items in the '%s' group\n",entry_name);
					error |= CBF_H5ERROR;
				}
			}

			/*
             Convert the axes after iterating through the file, when all of them have been found.
             
             TODO:
             I need unique names for each axis, so pick an '_n' suffix, with n being some integer,
             as an arbitrary scheme to break name collisions. Need to check any colliding items
             for the presence of collisions, then check the colliding names for this suffix and
             adjust it as needed to get non-colliding names.
             
             TODO:
             Extract the data from each axis dataset, storing it in the appropriate place in the
             CBF file: 'diffrn_scan_frame_axis' for data; 'axis' for metadata.
		*/
				if (CBF_SUCCESS == error) {
				cbf_axisData_t * const * it = NULL;
				cbf_axisData_t * const * const end = table->axisData+table->nAxes;
				/* Ensure I have unique names */
				for (it = table->axisData; end != it; ++it) {
					cbf_axisData_t * const * it2 = NULL;
					for (it2 = it, ++it2; end != it2; ++it2) {
						if (!strcmp((*it)->name,(*it2)->name)) {
							cbf_debug_print("warning: unhandled duplicate axis names found:");
							cbf_debug_print2("Duplicated name: %s\n",(*it)->name);
							error |= CBF_NOTIMPLEMENTED;
				}
			}
		}
                if (!error && nx->logfile) {
                    fputc('\n',nx->logfile);
                    int len = fprintf(nx->logfile,"Found %zu %s:\n",table->nAxes,table->nAxes != 1 ? "axes" : "axis");
                    while (--len > 0) fputc('-',nx->logfile);
                    fputc('\n',nx->logfile);
				}
                if (!error) { /* Do the conversion to CBF format */
					cbf_node * diffrn_measurement_axis = NULL;
					cbf_node * diffrn_detector_axis = NULL;
					cbf_node * diffrn_scan_frame_axis = NULL;
					cbf_node * axis = NULL;
                    double McStas2CBF[3][3];
                    double pgavec[3];
                    double norm_pgavec;
                    int ii, jj;
                    int havepga, havegravity, havesource;
                    double Q_McStas, U_McStas, psn_McStas;
					CBF_CALL(cbf_require_datablock(cbf,table->datablock_id));
					CBF_CALL(cbf_require_category(cbf,"diffrn_measurement_axis"));
					diffrn_measurement_axis = cbf->node;
					CBF_CALL(cbf_require_category(cbf,"diffrn_detector_axis"));
					diffrn_detector_axis = cbf->node;
					CBF_CALL(cbf_require_category(cbf,"diffrn_scan_frame_axis"));
					diffrn_scan_frame_axis = cbf->node;
					CBF_CALL(cbf_require_category(cbf,"axis"));
					axis = cbf->node;
                    /* extract the CBF coordinate system from the data
                       if there is a primary goniometer axis*/
                    havepga = havegravity = havesource = 0;
                    for (it = table->axisData; CBF_SUCCESS==error && end != it; ++it) {
                        hid_t attr = CBF_H5FAIL;
                        cbf_axisData_t * const axisData = *it;
                        if ((axisData->flags&CBF_AXIS_DATA_PGA) == 0) continue;
                        if (!cbf_H5Ivalid(attr=H5Aopen(axisData->axis,"vector",H5P_DEFAULT))) {
                            cbf_debug_print("couldn't open attribute");
                            error |= CBF_H5ERROR;
                        } else if (CBF_SUCCESS!=(error|=cbf_H5Aread(attr,H5T_NATIVE_DOUBLE,pgavec))) {
                            cbf_debug_print(cbf_strerror(error));
                        } else {
                            havepga = 1;
                        }
                        break;
                    }
                    if (havepga) {
                        double cbfZ[3];
                        double sourcedotX;
                        double norm_cbfZ;
                        norm_pgavec = cbf_norm(pgavec);
                        if (norm_pgavec < 1.e-38) {
                            error |= CBF_FORMAT;
                            cbf_debug_print(cbf_strerror(error));
                            havepga = 0;
                        } else {
                            CBF_CALL(cbf_scalar_product(1./norm_pgavec,pgavec,McStas2CBF[0]));
                        }
                        sourcedotX = -pgavec[2];
                        cbfZ[0] = cbfZ[1] = 0.;
                        cbfZ[2] = -1;
                        for (ii=0; ii < 0; ii++) {
                            cbfZ[ii] = cbfZ[ii]-sourcedotX*pgavec[ii];
                        }
                        norm_cbfZ = cbf_norm(cbfZ);
                        if (norm_cbfZ < 1.e-38) {
                            error |= CBF_FORMAT;
                            cbf_debug_print(cbf_strerror(error));
                            havepga = 0;
                        } else {
                            CBF_CALL(cbf_scalar_product(1./norm_cbfZ,cbfZ,McStas2CBF[2]));
                        }
                        
                        CBF_CALL(cbf_cross_product(cbfZ,McStas2CBF[0],McStas2CBF[1]));
                    }
                    if (!havepga) {
                        error |= CBF_FORMAT;
                        cbf_debug_print2("%s, failed to find valid primary goniometer axis\n",
                                         cbf_strerror(error));
                        for (ii=0;ii<3;ii++) {
                            for (jj=0;jj<3;jj++) {
                                McStas2CBF[ii][jj] = (ii==jj)?1.:0.;
                            }
                        }
                        McStas2CBF[0][0] = McStas2CBF[2][2] = -1.;
                    }
                    
                    /* At this point, I may have some incompletely processed Stokes vector
                       information still in the McStas coordinate system.  This requires
                       rotation of the second and third components of the vector.
                     
                       If esd's were provided, they need to be computed
                     
                    */
                    
                    if (CBF_SUCCESS==error &&
                        CBF_SUCCESS==cbf_find_category(cbf,"diffrn_radiation") &&
                        CBF_SUCCESS==cbf_find_column(cbf,"polarizn_source_norm_McStas") &&
                        CBF_SUCCESS==cbf_get_doublevalue(cbf,&psn_McStas)){
                        double phi;
                        phi = atan2(-McStas2CBF[1][0],McStas2CBF[1][1])*45./atan2(1.,1.);
                        CBF_CALL(cbf_set_column_name(cbf,"polarizn_source_norm"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",psn_McStas-phi));
                    }
                    if (CBF_SUCCESS==error &&
                        CBF_SUCCESS==cbf_find_category(cbf,"diffrn_radiation") &&
                        CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_Q_McStas") &&
                        CBF_SUCCESS==cbf_get_doublevalue(cbf,&Q_McStas) &&
                        CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_U_McStas") &&
                        CBF_SUCCESS==cbf_get_doublevalue(cbf,&U_McStas)){
                        double phi, Q_CBF, U_CBF, I_McStas;
                        double Q_McStas_esd, U_McStas_esd, I_McStas_esd;
                        double Q_CBF_esd, U_CBF_esd;
                        double psr, psr_esd, psn_esd;
                        phi = atan2(-McStas2CBF[1][0],McStas2CBF[1][1]);
                        Q_CBF = cos(2.*phi)*Q_McStas + sin(2.*phi)*U_McStas;
                        U_CBF = -sin(2.*phi)*Q_McStas + cos(2.*phi)*U_McStas;
                        CBF_CALL(cbf_find_column(cbf,"polarizn_Stokes_Q_McStas"));
                        CBF_CALL(cbf_set_column_name(cbf,"polarizn_Stokes_Q"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",Q_CBF));
                        CBF_CALL(cbf_find_column(cbf,"polarizn_Stokes_U_McStas"));
                        CBF_CALL(cbf_set_column_name(cbf,"polarizn_Stokes_U"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",U_CBF));
                        if (CBF_SUCCESS==error &&
                            CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_Q_McStas_esd") &&
                            CBF_SUCCESS==cbf_get_doublevalue(cbf,&Q_McStas_esd) &&
                            CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_U_McStas_esd") &&
                            CBF_SUCCESS==cbf_get_doublevalue(cbf,&U_McStas_esd)){
                            Q_CBF_esd = sqrt(cos(2.*phi)*Q_McStas_esd*cos(2.*phi)*Q_McStas_esd
                                             + sin(2.*phi)*U_McStas_esd*sin(2.*phi)*U_McStas_esd);
                            U_CBF_esd = sqrt(sin(2.*phi)*Q_McStas_esd*sin(2.*phi)*Q_McStas_esd
                                             + cos(2.*phi)*U_McStas_esd*cos(2.*phi)*U_McStas_esd);
                            CBF_CALL(cbf_find_column(cbf,"polarizn_Stokes_Q_McStas_esd"));
                            CBF_CALL(cbf_set_column_name(cbf,"polarizn_Stokes_Q_esd"));
                            CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",Q_CBF_esd));
                            CBF_CALL(cbf_find_column(cbf,"polarizn_Stokes_U_McStas_esd"));
                            CBF_CALL(cbf_set_column_name(cbf,"polarizn_Stokes_U_esd"));
                            CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",U_CBF_esd));
                            if (CBF_SUCCESS == error &&
                                CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_I_McStas") &&
                                CBF_SUCCESS==cbf_get_doublevalue(cbf,&I_McStas) &&
                                CBF_SUCCESS==cbf_find_column(cbf,"polarizn_Stokes_I_McStas_esd") &&
                                CBF_SUCCESS==cbf_get_doublevalue(cbf,&I_McStas_esd) &&
                                Q_McStas*Q_McStas+U_McStas*U_McStas > 0. &&
                                fabs(I_McStas)> 0.) {
                                psr = sqrt(Q_McStas*Q_McStas+U_McStas*U_McStas)/fabs(I_McStas);
                                psn_esd = ((22.5/atan2(1.,1.))*
                                           sqrt(Q_McStas*Q_McStas_esd*Q_McStas*Q_McStas_esd+
                                                U_McStas*U_McStas_esd*U_McStas*U_McStas_esd)/
                                           (Q_McStas*Q_McStas+U_McStas*U_McStas));
                                psr_esd = ((1./I_McStas)*(1./I_McStas)*
                                           sqrt(Q_McStas*Q_McStas_esd*Q_McStas*Q_McStas_esd+
                                                U_McStas*U_McStas_esd*U_McStas*U_McStas_esd+
                                                psr*I_McStas_esd*psr*I_McStas_esd));
                                CBF_CALL(cbf_require_column(cbf,"polarizn_source_norm_esd"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",psn_esd));
                                CBF_CALL(cbf_require_column(cbf,"polarizn_source_ratio"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%-.15g",psr_esd));
                            }
                        }
                    }
                    
					/* NOTE: this loop writes data to several tables simultaneously */
					for (it = table->axisData; CBF_SUCCESS==error && end != it; ++it) {
						cbf_axisData_t * const axisData = *it;
						unsigned int axisRow = 0;
						if (CBF_SUCCESS==error) {
							/* add a new row & convert the axis name */
							cbf->node = axis;
							CBF_CALL(cbf_require_column(cbf,"id"));
							CBF_CALL(cbf_new_row(cbf));
							axisRow = cbf->row;
							CBF_CALL(cbf_set_value(cbf,axisData->name));
                            if (!error && !cbf_cistrcmp(axisData->name,"GRAVITY")) havegravity = 1;
                            if (!error && !cbf_cistrcmp(axisData->name,"SOURCE")) havesource = 1;
                            if (!error && nx->logfile) fprintf(nx->logfile,"%s\n",axisData->name);
						}
						if (CBF_SUCCESS==error) {
							/* set the 'equipment' & add to any mapping tables for detectors & goniometers */
							CBF_CALL(cbf_require_column(cbf,"equipment"));
							if (axisEquipment_detector==axisData->equipment) {
								const int row = cbf->row;
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: detector\n");
								CBF_CALL(cbf_set_value(cbf,"detector"));
								cbf->node = diffrn_detector_axis;
								CBF_CALL(cbf_require_column(cbf,"detector_id"));
								CBF_CALL(cbf_new_row(cbf));
								CBF_CALL(cbf_set_value(cbf,table->diffrn_detector_id));
								CBF_CALL(cbf_require_column(cbf,"axis_id"));
								CBF_CALL(cbf_set_value(cbf,axisData->name));
								cbf->node = axis;
								cbf->row = row;
							} else if (axisEquipment_goniometer==axisData->equipment) {
								const int row = cbf->row;
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: goniometer\n");
								CBF_CALL(cbf_set_value(cbf,"goniometer"));
								cbf->node = diffrn_measurement_axis;
								CBF_CALL(cbf_require_column(cbf,"measurement_id"));
								CBF_CALL(cbf_new_row(cbf));
								CBF_CALL(cbf_set_value(cbf,diffrn_measurement_id));
								CBF_CALL(cbf_require_column(cbf,"axis_id"));
								CBF_CALL(cbf_set_value(cbf,axisData->name));
								cbf->node = axis;
								cbf->row = row;
							} else if (axisEquipment_image==axisData->equipment) {
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: image\n");
								CBF_CALL(cbf_set_value(cbf,"detector"));
							} else if (axisEquipment_gravity==axisData->equipment) {
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: gravity\n");
                                /* CBF_CALL(cbf_set_value(cbf,"gravity")); */
                                CBF_CALL(cbf_set_value(cbf,"general"));
							} else if (axisEquipment_source==axisData->equipment) {
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: source\n");
                                /* CBF_CALL(cbf_set_value(cbf,"source")); */
                                CBF_CALL(cbf_set_value(cbf,"general"));
							} else {
                                if (!error && nx->logfile) fprintf(nx->logfile,"Equipment: general\n");
								CBF_CALL(cbf_set_value(cbf,"general"));
							}
						}
						if (CBF_SUCCESS==error) { /* record the name of the axis that this depends on */
							cbf_axisData_t * const depends_on = axisData->depends_on;
							CBF_CALL(cbf_require_column(cbf,"depends_on"));
							if (depends_on) {
                                if (!error && nx->logfile) fprintf(nx->logfile,"Depends on: %s\n",depends_on->name);
								CBF_CALL(cbf_set_value(cbf,depends_on->name));
							} else CBF_CALL(cbf_set_value(cbf,"."));
						}
						if (CBF_SUCCESS==error) { /* extract the transformation type */
							hid_t attr = CBF_H5FAIL;
							const char * type = NULL;
							if (!cbf_H5Ivalid(attr=H5Aopen(axisData->axis,"transformation_type",H5P_DEFAULT))) {
								cbf_debug_print("couldn't open attribute");
								error |= CBF_H5ERROR;
							} else if (CBF_SUCCESS!=(error|=cbf_H5Aread_string(attr,&type))) {
								cbf_debug_print(cbf_strerror(error));
							} else {
								CBF_CALL(cbf_require_column(cbf,"type"));
								if (!strcmp(type,"translation")) {
									const hsize_t off[] = {nx->slice};
									const hsize_t cnt[] = {1};
									double val;
                                    if (!error && nx->logfile) fprintf(nx->logfile,"Type: translation\n");
									CBF_CALL(cbf_set_value(cbf,"translation"));
									if (axisEquipment_image!=axisData->equipment) {
										if (CBF_SUCCESS!=(error|=cbf_H5Dread2(axisData->axis,off,0,cnt,&val,H5T_NATIVE_DOUBLE))) {
											cbf_debug_print(cbf_strerror(error));
										} else {
											cbf->node = diffrn_scan_frame_axis;
											CBF_CALL(cbf_new_row(cbf));
											CBF_CALL(cbf_require_column(cbf,"axis_id"));
											CBF_CALL(cbf_set_value(cbf,axisData->name));
											CBF_CALL(cbf_require_column(cbf,"frame_id"));
											CBF_CALL(cbf_set_value(cbf,table->frame_id));
											CBF_CALL(cbf_require_column(cbf,"angle"));
											CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.0));
											CBF_CALL(cbf_require_column(cbf,"displacement"));
											CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",val));
										}
									}
								} else  if (!strcmp(type,"rotation")) {
									const hsize_t off[] = {nx->slice};
									const hsize_t cnt[] = {1};
									double val;
                                    if (!error && nx->logfile) fprintf(nx->logfile,"Type: rotation\n");
									CBF_CALL(cbf_set_value(cbf,"rotation"));
									if (axisEquipment_image!=axisData->equipment) {
										if (CBF_SUCCESS!=(error|=cbf_H5Dread2(axisData->axis,off,0,cnt,&val,H5T_NATIVE_DOUBLE))) {
											cbf_debug_print(cbf_strerror(error));
										} else {
											cbf->node = diffrn_scan_frame_axis;
											CBF_CALL(cbf_new_row(cbf));
											CBF_CALL(cbf_require_column(cbf,"axis_id"));
											CBF_CALL(cbf_set_value(cbf,axisData->name));
											CBF_CALL(cbf_require_column(cbf,"frame_id"));
											CBF_CALL(cbf_set_value(cbf,table->frame_id));
											CBF_CALL(cbf_require_column(cbf,"angle"));
											CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",val));
											CBF_CALL(cbf_require_column(cbf,"displacement"));
											CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.0));
										}
									}
								} else {
                                    if (!error && nx->logfile) fprintf(nx->logfile,"Type: general\n");
									CBF_CALL(cbf_set_value(cbf,"general"));
								}
								cbf->node = axis;
								cbf->row = axisRow;
							}
							free((void*)type);
							cbf_H5Afree(attr);
						}
						if (CBF_SUCCESS==error) { /* extract the vector */
							hid_t attr = CBF_H5FAIL;
							double vec[3];
							if (!cbf_H5Ivalid(attr=H5Aopen(axisData->axis,"vector",H5P_DEFAULT))) {
								cbf_debug_print("couldn't open attribute");
								error |= CBF_H5ERROR;
							} else if (CBF_SUCCESS!=(error|=cbf_H5Aread(attr,H5T_NATIVE_DOUBLE,vec))) {
								cbf_debug_print(cbf_strerror(error));
							} else {
                                double vector[3];
                                CBF_CALL(cbf_apply_matrix(McStas2CBF,vec,vector));
                                if (!error && nx->logfile) fprintf(nx->logfile,"Vector: [%g, %g, %g]\n",
                                                                   vector[0],vector[1],vector[2]);
								CBF_CALL(cbf_require_column(cbf,"vector[1]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",vector[0]));
								CBF_CALL(cbf_require_column(cbf,"vector[2]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",vector[1]));
								CBF_CALL(cbf_require_column(cbf,"vector[3]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",vector[2]));
							}
							cbf_H5Afree(attr);
						}
						/* extract the offset */
						if (!error) {
							htri_t has_offset = H5Aexists(axisData->axis,"offset");
							double off[3] = {0.,0.,0.};
                            double offset[3];
							if (has_offset<=0) {
								cbf_debug_print("couldn't check existence of attribute");
								error |= CBF_H5ERROR;
							} else if (has_offset>0) {
                                hid_t Aoffset = CBF_H5FAIL;
                                if (!cbf_H5Ivalid(Aoffset=H5Aopen(axisData->axis,"offset",H5P_DEFAULT))) {
									cbf_debug_print("couldn't open attribute");
									error |= CBF_H5ERROR;
                                } else if (error|=cbf_H5Aread(Aoffset,H5T_NATIVE_DOUBLE,off)) {
									cbf_debug_print("couldn't read attribute");
								} else {
									int found = CBF_SUCCESS;
									const char * unit_string = NULL;
									hid_t units = CBF_H5FAIL;
                                    CBF_CALL(cbf_apply_matrix(McStas2CBF,off,offset));
									found = cbf_H5Afind(axisData->axis,&units,"offset_units",CBF_H5FAIL,CBF_H5FAIL);
									if (CBF_NOTFOUND==found) {
										/*
                                         No 'offset_units' specified, can use 'units' iff 'type' is "translation".
                                         TODO: check the transformation type here
                                         */
										CBF_CALL(cbf_H5Afind(axisData->axis,&units,"units",CBF_H5FAIL,CBF_H5FAIL));
									} else if (found) {
										cbf_debug_print(cbf_strerror(found));
										error |= found;
									}
									CBF_CALL(cbf_H5Aread_string(units,&unit_string));
									if (!error) {
										/* need a conversion factor to apply to the offset before storing it */
										double factor = 0./0.;
                                        if (CBF_SUCCESS!=(error|=cbf_scale_units(unit_string,"mm",&factor))) {
											cbf_debug_print(cbf_strerror(error));
										} else {
											int i;
                                            if (!error && nx->logfile) fprintf(nx->logfile,"Offset: [%g, %g, %g]\n",offset[0]*factor,offset[1]*factor,offset[2]*factor);
                                            for (i = 0; i != 3; ++i) offset[i] *= factor;
										}
									}
									cbf_H5Afree(units);
									free((void*)unit_string);
								}
                                cbf_H5Afree(Aoffset);
							}
							if (!error) {
								CBF_CALL(cbf_require_column(cbf,"offset[1]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",offset[0]));
								CBF_CALL(cbf_require_column(cbf,"offset[2]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",offset[1]));
								CBF_CALL(cbf_require_column(cbf,"offset[3]"));
                                CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",offset[2]));
							}
						}
                        if (!error && nx->logfile) fputc('\n',nx->logfile);
					}
                    /* all real axes converted, add the gravity & beam axes to 
                     fully specify the coordinate system for future McStas conversions*/
                    if (!havegravity) {
                        double gravity[3] = {0.,-1.,0.};
                        double cbf_gravity[3];
                        CBF_CALL(cbf_apply_matrix(McStas2CBF,gravity,cbf_gravity));
					CBF_CALL(cbf_require_category(cbf,"axis"));
					/* gravity: */
					CBF_CALL(cbf_require_column(cbf,"id"));
					CBF_CALL(cbf_new_row(cbf));
					CBF_CALL(cbf_set_value(cbf,"GRAVITY"));
					CBF_CALL(cbf_require_column(cbf,"equipment"));
					CBF_CALL(cbf_set_value(cbf,"gravity"));
					CBF_CALL(cbf_require_column(cbf,"type"));
					CBF_CALL(cbf_set_value(cbf,"general"));
					CBF_CALL(cbf_require_column(cbf,"depends_on"));
					CBF_CALL(cbf_set_value(cbf,"."));
					CBF_CALL(cbf_require_column(cbf,"vector[1]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_gravity[0]));
					CBF_CALL(cbf_require_column(cbf,"vector[2]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_gravity[1]));
					CBF_CALL(cbf_require_column(cbf,"vector[3]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_gravity[2]));
					CBF_CALL(cbf_require_column(cbf,"offset[1]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
					CBF_CALL(cbf_require_column(cbf,"offset[2]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
					CBF_CALL(cbf_require_column(cbf,"offset[3]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
                    }
                    if (!havesource) {
                        double source[3] = {0.,0.,-1.};
                        double cbf_source[3];
                        CBF_CALL(cbf_apply_matrix(McStas2CBF,source,cbf_source));
                        CBF_CALL(cbf_require_category(cbf,"axis"));
					/* beam: */
					CBF_CALL(cbf_require_column(cbf,"id"));
					CBF_CALL(cbf_new_row(cbf));
					CBF_CALL(cbf_set_value(cbf,"SOURCE"));
					CBF_CALL(cbf_require_column(cbf,"equipment"));
					CBF_CALL(cbf_set_value(cbf,"source"));
					CBF_CALL(cbf_require_column(cbf,"type"));
					CBF_CALL(cbf_set_value(cbf,"general"));
					CBF_CALL(cbf_require_column(cbf,"depends_on"));
					CBF_CALL(cbf_set_value(cbf,"."));
					CBF_CALL(cbf_require_column(cbf,"vector[1]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_source[0]));
					CBF_CALL(cbf_require_column(cbf,"vector[2]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_source[1]));
					CBF_CALL(cbf_require_column(cbf,"vector[3]"));
                        CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",cbf_source[2]));
					CBF_CALL(cbf_require_column(cbf,"offset[1]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
					CBF_CALL(cbf_require_column(cbf,"offset[2]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
					CBF_CALL(cbf_require_column(cbf,"offset[3]"));
					CBF_CALL(cbf_set_doublevalue(cbf,"%.15g",0.));
				}
			}
            }

			/* free the key */
			_cbf_free_nx2cbf_key(table);

			/*
             Permute the CBF tree:
             The data should be written last, but the writer currently writes in order of creation.
             Columns should be sorted in alphabetical order in all tables, tables should be sorted
             in alphabetical order except for 'array_data' which should be last.
             */
			if (CBF_SUCCESS==error) {
				if (CBF_SUCCESS!=(error|=cbf_rewind_datablock(cbf))) {
					cbf_debug_print(cbf_strerror(error));
				} else {
					cbf_node * const db = cbf->node;
					cbf_node * const * const cat_end = db->child + db->children;
					cbf_node * const * pcat;
					/* sort each table */
					for (pcat = db->child; cat_end != pcat; ++pcat) {
						cbf_node * const cat = *pcat;
						if (!strcmp(cat->name,"array_data")) qsort(cat->child, cat->children, sizeof(void*), cmp_arraydata);
						else qsort(cat->child, cat->children, sizeof(void*), cmp_column);
					}
					/* sort the tables */
					qsort(db->child, db->children, sizeof(void*), cmp_category);
				}
			}
			free((void*)_array_id);
		}
        
		return error;
	}

	/*
	Find a suitable HDF5 datatype for the given parameters.
	*/
	static int cbf_find_array_data_h5type
			(hid_t * const type,
			 unsigned int bits,
			 int sign,
			 int real,
			 const char *byteorder)
	{
		int error = CBF_SUCCESS;
    
		cbf_debug_print("find_array_data_h5type\n");
    
		/* check arguments */
		if (!type) {
			cbf_debug_print("Invalid type pointer given\n");
			return CBF_ARGUMENT;
		}
		if (!byteorder) {
			cbf_debug_print("No byte order given\n");
			return CBF_ARGUMENT;
	}

		if (real) {
			const int order = ('l'==*byteorder||'L'==*byteorder) ? 0 : 1;
			if (!sign) error |= CBF_FORMAT;
			else {
				const hid_t tbl[2][2] = {
					{H5T_IEEE_F32LE,H5T_IEEE_F64LE},
					{H5T_IEEE_F32BE,H5T_IEEE_F64BE}
	};
				unsigned int idx = 2;
				idx = bits<=64 ? 1 : idx;
				idx = bits<=32 ? 0 : idx;
				if (idx > 1) error |= CBF_FORMAT;
				else *type = tbl[order][idx];
			}
		} else {
			const int order = ('l'==*byteorder||'L'==*byteorder) ? 0 : 1;
			/* define a lookup table for integer types */
			const hid_t tbl[2][2][4] = {
	{
					{H5T_STD_I8LE,H5T_STD_I16LE,H5T_STD_I32LE,H5T_STD_I64LE},
					{H5T_STD_U8LE,H5T_STD_U16LE,H5T_STD_U32LE,H5T_STD_U64LE}
				}, {
					{H5T_STD_I8BE,H5T_STD_I16BE,H5T_STD_I32BE,H5T_STD_I64BE},
					{H5T_STD_U8BE,H5T_STD_U16BE,H5T_STD_U32BE,H5T_STD_U64BE}
				}
	};
			/* select a value from the table */
			unsigned int idx = 4;
			idx = bits<=64 ? 3 : idx;
			idx = bits<=32 ? 2 : idx;
			idx = bits<=16 ? 1 : idx;
			idx = bits<=8  ? 0 : idx;
			if (idx > 3) error |= CBF_FORMAT;
			else *type = tbl[order][sign?0:1][idx];
		}
    
		return error;
	}
    
	/*
	Decompress the data selected in the handle, ensure an appropriate HDF5 dataset exists to store it,
	insert it a the given index with some parameter values set according to the given flags.
    
	Writes saturation_value and data to h5handle->nxdetector
     */
	static int cbf_write_array_h5file(const cbf_node * node,
     const unsigned int row,
			 cbf_h5handle h5handle,
			 const char * const saturation_value,
			 const char * const undefined_value,
			 hsize_t * dims)
	{
		int error = CBF_SUCCESS;
		cbf_debug_print("write_array_h5file\n");

		if (!node) {
			cbf_debug_print("Invalid node given\n");
			error |= CBF_ARGUMENT;
		} else if (!h5handle) {
			cbf_debug_print("Invalid hdf5 handle given\n");
			error |= CBF_ARGUMENT;
				} else {
			int found = CBF_SUCCESS, id, bits, sign, real;
			cbf_file *file;
			long start;
			const char *byteorder;
			size_t size, nelem, cbfdim[3], padding;
			unsigned int compression;
			hid_t h5type = CBF_H5FAIL;
			/* find the datatype and array size */
			CBF_CALL(cbf_get_bintext(node, row, NULL,
					 &id, &file, &start, &size,
					 NULL, NULL, &bits, &sign, &real,
					 &byteorder, &nelem, cbfdim+2, cbfdim+1, cbfdim+0, &padding,
					 &compression));
			CBF_CALL(cbf_find_array_data_h5type(&h5type,bits,sign,real,byteorder));

			if (dims) {
				dims[0] = 0;
				dims[1] = cbfdim[1];
				dims[2] = cbfdim[2];
				}

			/* check the saturation value */
			if (saturation_value) {
				hid_t dataset = CBF_H5FAIL;
				hsize_t max[] = {H5S_UNLIMITED};
				hsize_t cnk[] = {1};
				hsize_t off[] = {h5handle->slice};
				hsize_t cnt[] = {1};
                        hsize_t buf[] = {0};
				CBF_CALL(cbf_H5Drequire(h5handle->nxdetectors[h5handle->cur_detector],&dataset,"saturation_value",1,max,cnk,buf,h5type));
				if (real) {
					/* every float can be represented exactly by a double, so no need for float intermediate */
					const double num = strtod(saturation_value,0);
					CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_DOUBLE));
                    } else {
					if (sign) {
						/* use longest signed integer: all smaller types represent a subset of these values */
						const signed long num = strtol(saturation_value,0,10);
						CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_LONG));
					} else {
						/* use longest unsigned integer: all smaller types represent a subset of these values */
						const unsigned long num = strtoul(saturation_value,0,10);
						CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_ULONG));
                    }
                }
				cbf_H5Dfree(dataset);
                    }

			/* check the undefined value */
			if (undefined_value) {
				hid_t dataset = CBF_H5FAIL;
				hsize_t max[] = {H5S_UNLIMITED};
				hsize_t cnk[] = {1};
				hsize_t off[] = {h5handle->slice};
				hsize_t cnt[] = {1};
                        hsize_t buf[] = {0};
				CBF_CALL(cbf_H5Drequire(h5handle->nxdetectors[h5handle->cur_detector],&dataset,"undefined_value",1,max,cnk,buf,h5type));
				if (real) {
					/* every float can be represented exactly by a double, so no need for float intermediate */
					const double num = strtod(undefined_value,0);
					CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_DOUBLE));
                    } else {
					if (sign) {
						/* use longest signed integer: all smaller types represent a subset of these values */
						const signed long num = strtol(undefined_value,0,10);
						CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_LONG));
					} else {
						/* use longest unsigned integer: all smaller types represent a subset of these values */
						const unsigned long num = strtoul(undefined_value,0,10);
						CBF_CALL(cbf_H5Dinsert(dataset,off,0,cnt,buf,&num,H5T_NATIVE_ULONG));
                    }
                }
				cbf_H5Dfree(dataset);
                }

			/* allocate space for the decompressed data */
			if (CBF_SUCCESS == error) {
				void * value;
				const unsigned int elsize = (bits+7)/8;
				size_t nelem_read;
				const int rank = 3;
				hsize_t buf[] = {0, 0, 0};
				hsize_t h5dim[] = {0, cbfdim[1], cbfdim[2]};
				hsize_t h5max[] = {H5S_UNLIMITED, cbfdim[1], cbfdim[2]};
				hsize_t h5chunk[] = {1, cbfdim[1], cbfdim[2]};
				hid_t dset = CBF_H5FAIL;
				value = malloc(nelem*elsize);
				CBF_CALL(cbf_set_fileposition(file, start, SEEK_SET));
				CBF_CALL(cbf_decompress_parameters(NULL, NULL, NULL, NULL, NULL, NULL, NULL, compression, file));
                {
					cbf_debug_print2("masked compression: %d\n",compression&CBF_COMPRESSION_MASK);
					cbf_debug_print("compression type: ");
					if (compression == CBF_CANONICAL) {
                        cbf_debug_print("CBF_CANONICAL\n");
                    } else if ((compression&CBF_COMPRESSION_MASK) == CBF_PACKED){
                        cbf_debug_print("CBF_PACKED\n");
                    } else if ((compression&CBF_COMPRESSION_MASK) == CBF_PACKED_V2) {
                        cbf_debug_print("CBF_PACKED_V2\n");
                    } else if (compression == CBF_BYTE_OFFSET) {
                        cbf_debug_print("CBF_BYTE_OFFSET\n");
                    } else if (compression == CBF_NIBBLE_OFFSET) {
                        cbf_debug_print("CBF_NIBBLE_OFFSET\n");
                    } else if (compression == CBF_PREDICTOR) {
                        cbf_debug_print("CBF_PREDICTOR\n");
                    } else if (compression == CBF_NONE) {
                        cbf_debug_print("CBF_NONE\n");
                    } else {
                        cbf_debug_print("Unknown\n");
                }
					cbf_debug_print2("element size: %d\n",(unsigned int)(elsize));
					cbf_debug_print2("real?: %s\n",real?"yes":"no");
                }

				/* ensure a dataset exists in the detector */
				found =  cbf_H5Dfind2(h5handle->nxdetectors[h5handle->cur_detector],
                                      &dset,"data",rank,h5max,buf,h5type);
				if (CBF_SUCCESS==found) {
				} else if (CBF_NOTFOUND==found) {
					/* define variables & check args */
					hid_t dataSpace = CBF_H5FAIL;
					hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);

					/* check variables are valid */
					CBF_CALL(cbf_H5Screate(&dataSpace, rank, h5dim, h5max));

					/* allow dataset to be chunked */
					CBF_H5CALL(H5Pset_chunk(dcpl,rank,h5chunk));
					/* allow compression */
					if (CBF_SUCCESS==error) {
						if (h5handle->flags & CBF_H5COMPRESSION_ZLIB) {
							H5Pset_deflate(dcpl, 1);
						} else if (h5handle->flags & CBF_H5COMPRESSION_CBF) {
							unsigned int cd_values[CBF_H5Z_FILTER_CBF_NELMTS];
							cd_values[CBF_H5Z_FILTER_CBF_COMPRESSION] = compression;
							cd_values[CBF_H5Z_FILTER_CBF_RESERVED]    = 0;
							cd_values[CBF_H5Z_FILTER_CBF_BINARY_ID]   = id;
							cd_values[CBF_H5Z_FILTER_CBF_PADDING]     = padding;
							cd_values[CBF_H5Z_FILTER_CBF_ELSIZE]      = elsize;
							cd_values[CBF_H5Z_FILTER_CBF_ELSIGN]      = sign;
							cd_values[CBF_H5Z_FILTER_CBF_REAL]        = real;
							cd_values[CBF_H5Z_FILTER_CBF_DIMFAST]     = *(h5chunk+2);
							cd_values[CBF_H5Z_FILTER_CBF_DIMMID]      = *(h5chunk+1);
							cd_values[CBF_H5Z_FILTER_CBF_DIMSLOW]     = *(h5chunk+0);

							if (h5handle->flags & CBF_H5_REGISTER_COMPRESSIONS) {
								if (!H5Zfilter_avail(CBF_H5Z_FILTER_CBF)) {
									CBF_H5CALL(H5Zregister(CBF_H5Z_CBF));
            }
        }

							CBF_H5CALL(H5Pset_filter(dcpl, CBF_H5Z_FILTER_CBF, H5Z_FLAG_OPTIONAL, CBF_H5Z_FILTER_CBF_NELMTS, cd_values));

		}
		}

					/* create the dataset */
					if (CBF_SUCCESS == error)
						dset = H5Dcreate2(h5handle->nxdetectors[h5handle->cur_detector],"data",h5type,dataSpace,H5P_DEFAULT,dcpl,H5P_DEFAULT);

					/* check local variables are properly closed */
					if (cbf_H5Ivalid(dataSpace)) H5Sclose(dataSpace);
					if (cbf_H5Ivalid(dcpl)) H5Pclose(dcpl);
            } else {
					error |= found;
					cbf_debug_print2("error locating primary dataset: %s\n", cbf_strerror(found));
		}
                    if (CBF_SUCCESS==error) {
					const hsize_t h5offset[] = {h5handle->slice, 0, 0};
					const int sig[] = {1};
					int sigbuf[] = {0};

					/* extract the image data from CBF */
					CBF_CALL(cbf_decompress(value, elsize, sign, nelem, &nelem_read,
							 size, compression, bits, sign, file, real, byteorder,
							 nelem, cbfdim[2], cbfdim[1], cbfdim[0], padding));
					if (nelem_read != nelem) error |= CBF_ENDOFDATA;

					/* store the image data in HDF5 */
					CBF_CALL(cbf_H5Dinsert(dset,h5offset,0,h5chunk,buf,value,h5type));
					CBF_CALL(CBFM_H5Arequire_cmp2(dset,"signal",0,0,H5T_STD_I32LE,H5T_NATIVE_INT,sig,sigbuf,cmp_int,0));
					cbf_H5Dfree(dset);
					free((void*)value);
		}
		}
                }

		return error;
                    }

                    /*
	A primary key may be an integer or a string, I need to allow them both to be compared
	for equality. This function must return 0 if the keys are considered equal, and
	non-zero otherwise. Note that this means 'strcmp' is a valid comparison function.
                     */
	typedef int (*key_cmp_func)(const char *, const char *);

	/* Define the signature of a function to extract a value from a 'cbf_cbf2nx_key_t' object. */
	typedef const char * (*key_get_value_func)(const cbf_cbf2nx_key_t * const);

	/*
	Each key is defined by a column name. A method of comparing values for equality
	and value to compare against allows rows to be discarded if not relevant.
	*/
	typedef struct cbf_primary_key_t
	{
		/* a unique identifier */
		const char * name;
		/* parameterised behaviour */
		key_get_value_func getValue;
		key_cmp_func cmp;
	} cbf_primary_key_t;
        
	/*
	count the number of valid keys that are pointed to by 'begin'.
	*/
	static size_t cbf_count_primary_keys
			(const cbf_primary_key_t * begin)
	{
		if (!begin) {
			return 0;
		} else {
			const cbf_primary_key_t * end = begin;
			while (end->name) ++end;
			return end-begin;
					}
				}

			/*
	Test if an array of pointers of given length contains a given pointer.
	If an invalid (null) array is given then it contains nothing.
	Returns non-zero if the pointer 'value' is in the array, zero otherwise.
             */
	static int array_contains
			(const void * const * const begin,
			 const size_t size,
			 const void * const value)
				{
		if (!begin) {
			return 0;
		} else {
			const void * const * it;
			const void * const end = size+begin;
			for (it = begin; end != it; ++it)
				if (value == *it)
					return 1;
				}
		return 0;
				}

					/*
	Locate the column for each primary key of the category, and cache both the column and its requested value for later use.
					*/
	static int cbf_populate_primaryKey_cache
			(cbf_primary_key_t * const primary_keys,
			 cbf_node * * * const primary_key_column,
			 const char * * * const primary_key_value,
			 const cbf_cbf2nx_key_t * const key,
			 cbf_node * const category)
	{
		int error = CBF_SUCCESS;
		if (!primary_keys || !primary_key_column || !key || !category) {
			error |= CBF_ARGUMENT;
		} else if (!(*primary_key_column=malloc(cbf_count_primary_keys(primary_keys)*sizeof(cbf_node*)))) {
			error |= CBF_ALLOC;
		} else if (!(*primary_key_value=malloc(cbf_count_primary_keys(primary_keys)*sizeof(const char*)))) {
			error |= CBF_ALLOC;
					} else {
			cbf_primary_key_t * it;
			for (it = primary_keys; !error && it->name; ++it) {
				/* reset the values in the cache */
				(*primary_key_column)[it-primary_keys] = NULL;
				/* attempt to set the column */
				const int found = cbf_find_child((*primary_key_column)+(it-primary_keys), category, it->name);
				if (CBF_NOTFOUND==found) {
					cbf_debug_print3("warning: '%s.%s' not found\n",category->name,it->name);
					(*primary_key_column)[it-primary_keys] = NULL;
				} else if (CBF_SUCCESS!=found) {
					if (1) {
						cbf_debug_print3("error: problem finding '%s.%s'\n",category->name,it->name);
						cbf_debug_print2("error: %s\n",cbf_strerror(found));
					}
					error |= found;
							}
				/* cache the values of primary keys */
				if (it->getValue) (*primary_key_value)[it-primary_keys] = it->getValue(key);
				else (*primary_key_value)[it-primary_keys] = NULL;
						}
					}
		return error;
	}
    
	/*
	Extract a set of matching rows from the given primary keys of a cbf category, looking up rows in the cached
	columns and comparing data to the cached values.

	Occasionally, a malformed file will be missing a column in a different table that defines the set of valid
	values for a foreign key in the current table. In this case all values for the degenerate row must compare equal
	within the matching row set that would be obtained if the degenerate key was ignored. If the values of such a
	column were allowed to differ then this would match columns that don't belong to the same item in the parent
	table.
	*/
	static int cbf_get_matching_rows
			(cbf_primary_key_t * const primary_keys,
			 cbf_node * const * const primary_key_column,
			 const char * const * const primary_key_value,
			 const unsigned int nRows,
			 unsigned int * * const row_set,
			 unsigned int * const mRows)
	{
		int error = CBF_SUCCESS;
		if (!primary_keys || !primary_key_column || !row_set || !mRows) {
			error |= CBF_ARGUMENT;
					} else {
			if (!(*row_set=malloc(sizeof(unsigned int)*nRows))) {
				error |= CBF_ALLOC;
				} else {
				unsigned int row;
				cbf_primary_key_t * it;
				*mRows = 0;
				/* use well-defined keys to extract a set of matching rows */
				for (row = 0; !error && row != nRows; ++row) {
					int row_matches = 1;
					cbf_primary_key_t * it;
					for (it = primary_keys; !error && it->name; ++it) {
						cbf_node * const column = primary_key_column[it-primary_keys];
						const char * const value = primary_key_value[it-primary_keys];
						if (column && value) {
					const char * val = NULL;
							if ((error|=cbf_node_get_value(column, row, &val))) {
								cbf_debug_print2("error: %s\n",cbf_strerror(error));
							} else {
								if (it->cmp(value,val)) row_matches = 0;
						}
						}
						}
					if (row_matches) (*row_set)[(*mRows)++] = row;
						}
				if (*mRows) {
					/* check that values given for degenerate keys are consistent within the set */
					for (it = primary_keys; !error && it->name; ++it) {
						cbf_node * const column = primary_key_column[it-primary_keys];
						const char * const value = primary_key_value[it-primary_keys];
						if (column && !value) {
							const char * ref = NULL;
							/* 'mRows' is unsigned and non-zero, so 'rows[0]' is valid and starting iterations from '1' is safe */
							CBF_CALL(cbf_node_get_value(column, (*row_set)[0], &ref));
							for (row = 1; !error && row != *mRows; ++row) {
								const char * val = NULL;
								CBF_CALL(cbf_node_get_value(column, (*row_set)[row], &val));
								if (!error && it->cmp(ref,val)) {
									cbf_debug_print2("error: inconsistent values for degenerate key '%s'\n",it->name);
									error |= CBF_FORMAT;
						}
					}
				}
			}
		}
				}
			}
		return error;
	}

	/* typedef to match the signature of the 'cbf_h5handle_require_xyzzy' functions */
	typedef int (*get_h5group_func)(cbf_h5handle, hid_t *, const char *);

	/*
	Conversion filter function signatures for various kinds of data:
	- strings should be converted by producing a new string that should be free'd.
	- numbers should be converted via a '*out = f(in)' process.
	- a NULL function pointer should indicate that no conversion filter is required.
	*/
	typedef void (*filter_func)();
	typedef int (*filter_string_func)(const char * const in, const char * * const out);
	typedef int (*filter_double_func)(const double in, double * const out);

	/* conversion function for inhomogeneity, to introduce a factor of 2 in the conversion */
	int filter_inhomogeneity
			(const double in,
			 double * const out)
	{
		int error = CBF_SUCCESS;
		if (!out) {
			error |= CBF_ARGUMENT;
		} else {
			*out = 2.0*in;
		}
		return error;
		}

			/*
	Define the possible mapping types, which will affect how a pointer is dereferenced later on.
             */
	enum mapping_type {
		/* ignore this item - no mapping wanted */
		CBF_MAP_NONE,
		/* convert to a nexus field */
		CBF_MAP_DATA,
        CBF_MAP_DATA_DEPRECATED,
		/* extract a key value */
		CBF_MAP_KEY,
		/*
		Store data from a column so it can be used via a callback function
		once all columns in the current row have been processed.
		*/
		CBF_MAP_CACHE,
	};

	/*
	A list of parameters to pass to a hypothetical 'cbf_nexus_dataset_with_units_require_cmp'
	function, which can be created using existing functionality but is extremely specialised.
	*/
	typedef struct cbf2nx_item_datamap_t
				{
		const char * name;
		const char * units;
		get_h5group_func get_object;
		filter_func filter;
		int rank;
	} cbf2nx_item_datamap_t;

	/* Conversion function for an item of data. */
	typedef int (*convert_func)(cbf_node *, const unsigned int, cbf_h5handle, const cbf2nx_item_datamap_t *);

	/* Single object to store both a conversion function and its data, for reference by 'cbf2nx_column_map_t'. */
	typedef struct cbf2nx_convert_t {
		convert_func convert;
		cbf2nx_item_datamap_t data;
	} cbf2nx_convert_t;

	/* Define the signature of a function to be used to set a specific value in the 'key' object. */
	typedef int (*set_key_func)(cbf_cbf2nx_key_t *, const char *);

	/* Add a layer of indirection. */
	typedef struct cbf2nx_set_key_t {
		set_key_func set_key;
	} cbf2nx_set_key_t;

	/* Define the signature of a function to cache the value at 'arg_0[arg_1]' in the cache object given by 'arg_2'. */
	typedef int (*cache_item_func)(cbf_node *, const unsigned int, void *);

	/* Add a layer of indirection. */
	typedef struct cbf2nx_cache_item_t {
		cache_item_func cache_item;
	} cbf2nx_cache_item_t;

	/* map an item name to some (discriminated) parameters used for converting it */
	typedef struct cbf2nx_column_map_t
	{
		const char * name;
		enum mapping_type type;
		const void * data;
	} cbf2nx_column_map_t;

	/* define the information required to manage the lifetime of a cache object */
	typedef struct cbf2nx_cache_t
	{
		size_t size; /*< the size of the cache object to be allocated */
		int (*ctor) (void * self); /*< initialise 'self' to a standard state */
		int (*dtor)(void * self); /*< free any allocated memory in 'self' */
	} cbf2nx_cache_t;

	/* define function signatures to per-row and per-table cache processing functions */
	typedef int (*process_row_func)(cbf_node *, cbf_h5handle, cbf_cbf2nx_key_t *, void *, void *, const unsigned int);
	typedef int (*process_tbl_func)(cbf_node *, cbf_h5handle, cbf_cbf2nx_key_t *, void *);

	/*
	Map a category name to an array of primary keys, data which it may contain and cache
	objects & processing functions for each row and for the whole set of matched rows.
	*/
	typedef struct cbf2nx_category_map_t
	{
		const char * name;
		cbf_primary_key_t * key_data;
		cbf2nx_column_map_t * column_data;
		cbf2nx_cache_t row_cache;
		process_row_func process_row;
		cbf2nx_cache_t tbl_cache;
		process_tbl_func process_tbl;
	} cbf2nx_category_map_t;


	/*
	Define some functions for manipulating caches of per-row data for various parts of the conversion process
	For each kind of cahce required I need to define:
	- a type
	- functions to manage its lifetime
	- functions to populate it
	- a function to use it
	*/

	/*
	Many caches make use of a simple method of adding string or floating-point data,
	these should turn all the boilerplate code to do that into one-liners.
	*/
#define DECL_CACHE_STR_SETTER(FUNCTION_NAME, CACHE_TYPE, CACHE_MEMBER) \
static int FUNCTION_NAME \
	(cbf_node * const column, \
	const unsigned int row, \
	void * const cache) \
{ \
	int error = CBF_SUCCESS; \
	CACHE_TYPE * const c = cache; \
	if (!column || !c) { \
		error |= CBF_ARGUMENT; \
} else { \
		error |= cbf_node_get_value(column, row, &c->CACHE_MEMBER); \
} \
	return error; \
		}

#define DECL_CACHE_DOUBLE_SETTER(FUNCTION_NAME, CACHE_TYPE, CACHE_MEMBER) \
static int FUNCTION_NAME \
	(cbf_node * const column, \
	const unsigned int row, \
	void * const cache) \
{ \
	int error = CBF_SUCCESS; \
	CACHE_TYPE * const c = cache; \
	if (!column || !c) { \
		error |= CBF_ARGUMENT; \
} else { \
		error |= cbf_node_get_doublevalue(column, row, &c->CACHE_MEMBER); \
} \
	return error; \
		}

#define DECL_CACHE_UINT_SETTER(FUNCTION_NAME, CACHE_TYPE, CACHE_MEMBER) \
static int FUNCTION_NAME \
	(cbf_node * const column, \
	const unsigned int row, \
	void * const cache) \
{ \
	int error = CBF_SUCCESS; \
	CACHE_TYPE * const c = cache; \
	if (!column || !c) { \
		error |= CBF_ARGUMENT; \
} else { \
		error |= cbf_node_get_uintvalue(column, row, &c->CACHE_MEMBER); \
} \
	return error; \
				}

#define DECL_CACHE_NODE_SETTER(FUNCTION_NAME, CACHE_TYPE, CACHE_MEMBER) \
static int FUNCTION_NAME \
	(cbf_node * const column, \
	const unsigned int row, \
	void * const cache) \
{ \
	int error = CBF_SUCCESS; \
	CACHE_TYPE * const c = cache; \
	CBF_UNUSED(row); \
	if (!column || !c) { \
		error |= CBF_ARGUMENT; \
	} else { \
		c->CACHE_MEMBER = column; \
	} \
	return error; \
}

					/*
	Define a type, constructor and setters to use when processing a single row of the 'array_data' table.
                     */
	typedef struct ArrayDataCache
	{
		cbf_node * column;
		unsigned int row;
	} ArrayDataCache;

	static int ctor_ArrayDataCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		ArrayDataCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
					} else {
			c->column = NULL;
			c->row = 0;
								}
		return error;
	}

	static int cache_ArrayData_data
			(cbf_node * const column,
			 const unsigned int row,
			 void * const cache)
		{
		int error = CBF_SUCCESS;
		ArrayDataCache * const c = cache;
		if (!column || !c) {
			error |= CBF_ARGUMENT;
		} else {
			c->column = column;
			c->row = row;
					}
		return error;
				}

			/*
	Process data from a single row of 'array_data'.

	This just needs to extract some data from the 'key' object and call a function
	which is also used when converting minicbf data to nexus data.
             */
	static int process_ArrayDataCache
    (cbf_node * const category,
     cbf_h5handle nx,
     cbf_cbf2nx_key_t * const key,
     void * const rcache,
     void * const tcache,
     const unsigned int row)
				{
		int error = CBF_SUCCESS;
		ArrayDataCache * const c = rcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !c || tcache) {
			error |= CBF_ARGUMENT;
		} else {
			if (!c->column) {
				cbf_debug_print("error: no data located");
			} else {
				CBF_CALL(cbf_write_array_h5file(c->column,c->row,nx,key->data_overload,key->data_undefined,0));
					}
					}
		return error;
				}

					/*
	Define a type, constructor and setters to use when processing a single row of the 'diffrn_radiation' table.
                     */
	typedef struct DiffrnRadiationRowCache
	{
		cbf_node * stokes_I;
		cbf_node * stokes_Q;
		cbf_node * stokes_U;
		cbf_node * stokes_V;
		cbf_node * psn;
		cbf_node * psr;
        cbf_node * stokes_I_esd;
		cbf_node * stokes_Q_esd;
		cbf_node * stokes_U_esd;
		cbf_node * stokes_V_esd;
		cbf_node * psn_esd;
		cbf_node * psr_esd;

	} DiffrnRadiationRowCache;

	static int ctor_DiffrnRadiationRowCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnRadiationRowCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
					} else {
			c->stokes_I = NULL;
			c->stokes_Q = NULL;
			c->stokes_U = NULL;
			c->stokes_V = NULL;
			c->psn = NULL;
			c->psr = NULL;
			c->stokes_I_esd = NULL;
			c->stokes_Q_esd = NULL;
			c->stokes_U_esd = NULL;
			c->stokes_V_esd = NULL;
			c->psn_esd = NULL;
			c->psr_esd = NULL;
					}
		return error;
	}
    
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_I, DiffrnRadiationRowCache, stokes_I);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_Q, DiffrnRadiationRowCache, stokes_Q);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_U, DiffrnRadiationRowCache, stokes_U);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_V, DiffrnRadiationRowCache, stokes_V);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_PSN, DiffrnRadiationRowCache, psn);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_PSR, DiffrnRadiationRowCache, psr);
    DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_I_ESD, DiffrnRadiationRowCache, stokes_I_esd);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_Q_ESD, DiffrnRadiationRowCache, stokes_Q_esd);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_U_ESD, DiffrnRadiationRowCache, stokes_U_esd);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_V_ESD, DiffrnRadiationRowCache, stokes_V_esd);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_PSN_ESD, DiffrnRadiationRowCache, psn_esd);
	DECL_CACHE_NODE_SETTER(cache_DiffrnRadiation_PSR_ESD, DiffrnRadiationRowCache, psr_esd);

    
	/*
	Process data from a single row of 'diffrn_radiation'.

	Calculate some of the stokes parameters and make reasonable assumptions for those
	which can't be identified with sufficient reliability (ie: intensity, which is not
	present in CBF in a usable form; and circular polarisation, which is not present
	in CBF in any form). Write the data to the appropriate place in nexus.

	 If the stokes vector is properly specified then the 2-parameter polarisation
     is ignored.
     
     
     Stokes_I:  Ip+In, where where Ip is the intensity
     (amplitude squared) of the electric vector in the
     plane of polarization and In is the intensity
     (amplitude squared) of the electric vector in the
     plane of the normal to the plane of polarization.
     
     Stokes_Q:  (Ip-In)*cos(2*theta), where where Ip is
     the intensity (amplitude squared) of the electric vector
     in the plane of polarization, In is the intensity
     (amplitude squared) of the electric vector in the plane
     of the normal to the plane of polarization, and theta
     is the angle as viewed from the specimen, between the
     normal to the polarization plane and the laboratory Y
     axis.
     
     Stokes_U:  (Ip-In)*sin(2*theta), where where Ip is
     the intensity (amplitude squared) of the electric vector
     in the plane of polarization, In is the intensity
     (amplitude squared) of the electric vector in the plane
     of the normal to the plane of polarization, and theta is
     the angle as viewed from the specimen, between the normal
     to the polarization plane and the laboratory Y axis.
     
     Stokes_V:  +/-2*sqrt(IpIn), with a + sign for right-handed
     circular polarization, where where Ip is the intensity
     (amplitude squared) of the electric vector in the plane of
     polarization and In is the intensity (amplitude squared) of
     the electric vector in the plane of the normal to the plane 
     of polarization, and theta is the angle as viewed from the
     specimen, between the normal to the polarization plane
     and the laboratory Y axis.
     
     The theta referred to in Stokes_Q and Stokes_U is that same
     as the value of _diffrn_radiation.polarizn_source_norm,
     and depends on the choice of laboratory coordinate systems.
     In particular, that angle may change between the CBF laboratory
     coordinate system and the NeXus McStas coordinate system.  In
     all cases the normal to the polarization plane is assumed to
     be orthogonal to the direction of the beam
     
     
     Looking head-on at the beam from sample to source, we have
     
     
            \             |  CIF_Y [0,1,0]
             \            |
              \           |    | nx_y (nexus Y axis)
               \          |    |
                \         |    /   
                 \        |   |
         normal   \       |   |
   to polarization \      |   /
         plane      \     |  |
    (in this case    \    |  |
     theta =+45 deg)  \   |  /
                       \  | |
                        \ | |
                         \|/
     
     In this example, nx_y is at a negative angle. phi, from
     CIF_Y, and the new value of nx_theta with be increased
     by -phi.  
       nx_Stokes_Q = cos(2*phi)*Stokes_Q+sin(2*phi)*Stokes_U
       nx_Stokes_U = cos(2*phi)*Stokes_U-sin(2*phi)*Stohes_Q
     
	*/
	static int process_DiffrnRadiationRowCache
    (cbf_node * const category,
     cbf_h5handle nx,
     cbf_cbf2nx_key_t * const key,
     void * const rcache,
     void * const tcache,
     const unsigned int row)
	{
		int error = CBF_SUCCESS;
		DiffrnRadiationRowCache * const c = rcache;
		if (!category || !nx || !key || !c || tcache) {
			error |= CBF_ARGUMENT;
		} else {
			/* get the angle to rotate from cbf to nexus polarisation coordinate frames */
			cbf_node * axes = NULL;
			double beam_dirn[3] = {0.0,0.0,0.0};
			double gravity_dirn[3] = {0.0,0.0,0.0};
			double x_nx[3] = {0.0,0.0,0.0};
			double y_nx[3] = {0.0,0.0,0.0};
			double phi = 0.0;
			CBF_CALL(cbf_find_parent(&axes,category,CBF_DATABLOCK));
			CBF_CALL(cbf_find_child(&axes,axes,"axis"));
			CBF_CALL(cbf_node_get_beam_dirn(axes, beam_dirn));
			CBF_CALL(cbf_node_get_gravity_dirn(axes, gravity_dirn));
			CBF_CALL(cbf_cross_product(beam_dirn,gravity_dirn,x_nx));
			CBF_CALL(cbf_cross_product(beam_dirn,x_nx,y_nx));
			if (!error) {
				phi = atan2(-y_nx[0],y_nx[1]);
			}
			/* store computed data in nexus, if all went well */
			if (!error) {
				int have_data = 0;
                int have_data_esds = 0;
				double value[4] = {0.0,0.0,0.0,0.0};
                double value_esds[4] = {0.0,0.0,0.0,0.0};
				if (
					cbf_node_has_doublevalue(c->stokes_I,row) &&
					cbf_node_has_doublevalue(c->stokes_Q,row) &&
					cbf_node_has_doublevalue(c->stokes_U,row) &&
					cbf_node_has_doublevalue(c->stokes_V,row)
				)
				{
					double Q = 0.0, U = 0.0;
					/* I have all the relevant columns for a stokes vector */
					CBF_CALL(cbf_node_get_doublevalue(c->stokes_I,row,value+0));
					CBF_CALL(cbf_node_get_doublevalue(c->stokes_Q,row,&Q));
					CBF_CALL(cbf_node_get_doublevalue(c->stokes_U,row,&U));
					CBF_CALL(cbf_node_get_doublevalue(c->stokes_V,row,value+3));
					value[1] = cos(2.*phi)*Q - sin(2.*phi)*U;
					value[2] = +sin(2.*phi)*Q + cos(2.*phi)*U;
					have_data = 1;
                    if (
                        cbf_node_has_doublevalue(c->stokes_I_esd,row) &&
                        cbf_node_has_doublevalue(c->stokes_Q_esd,row) &&
                        cbf_node_has_doublevalue(c->stokes_U_esd,row) &&
                        cbf_node_has_doublevalue(c->stokes_V_esd,row)
                        )
                    {
                        double Q_esd = 0.0, U_esd = 0.0;
                        /* The uncertainties are estimated by the square
                         root of the sum of the squares of the component
                         uncertainties */
                        CBF_CALL(cbf_node_get_doublevalue(c->stokes_I_esd,row,value_esds+0));
                        CBF_CALL(cbf_node_get_doublevalue(c->stokes_Q_esd,row,&Q_esd));
                        CBF_CALL(cbf_node_get_doublevalue(c->stokes_U_esd,row,&U_esd));
                        CBF_CALL(cbf_node_get_doublevalue(c->stokes_V_esd,row,value_esds+3));
                        value_esds[1] = sqrt(cos(2.*phi)*Q_esd*cos(2.*phi)*Q_esd
                                             + sin(2.*phi)*U_esd*sin(2.*phi)*U_esd);
                        value_esds[2] = sqrt(sin(2.*phi)*Q_esd*sin(2.*phi)*Q_esd
                                             + cos(2.*phi)*U_esd*cos(2.*phi)*U_esd);
                        have_data_esds = 1;
                    }
                    
				} else if (
					cbf_node_has_doublevalue(c->psn,row) &&
					cbf_node_has_doublevalue(c->psr,row)
				)
				{
					/*
					I don't have a valid stokes vector, but I do have a valid
					2-parameter representation that I know how to convert
                     if we assume no circular component.
					*/
					double psn = 0.0, psr = 0.0;
					CBF_CALL(cbf_node_get_doublevalue(c->psn,row,&psn));
					CBF_CALL(cbf_node_get_doublevalue(c->psr,row,&psr));
					psn *= atan2(1.,1.)/45.0;
					value[0] = 1.0;
					value[1] = psr*cos(2.*(psn+phi));
					value[2] = psr*sin(2.*(psn+phi));
					value[3] = 0.0;  /* No circular component assumed */
					have_data = 1;
                    if (
                        cbf_node_has_doublevalue(c->psn_esd,row) &&
                        cbf_node_has_doublevalue(c->psr_esd,row)
                        )
                    { double psn_esd = 0.0, psr_esd = 0.0;
                        /* The uncertainties are estimated by the square
                         root of the sum of the squares of the component
                         uncertainties.  In this case we are apprximating
                         with differentials.  This is only valid for small
                         uncertainties */
                        
                        CBF_CALL(cbf_node_get_doublevalue(c->psn_esd,row,&psn_esd));
                        CBF_CALL(cbf_node_get_doublevalue(c->psr_esd,row,&psr_esd));
                        value_esds[0] = 0.;
                        value_esds[1] = sqrt(cos(2.*(psn+phi))*psr_esd*cos(2.*(psn+phi))*psr_esd
                                              + 4*value[2]*psn_esd*value[2]*psn_esd);
                        
                        value_esds[2] = sqrt(sin(2.*(psn+phi))*psr_esd*sin(2.*(psn+phi))*psr_esd
                                              + 4*value[1]*psn_esd*value[1]*psn_esd);
                        value_esds[3] = 0.;
                        have_data_esds = 1;
				}
				}
				if (!error && have_data) {
					hid_t dset = CBF_H5FAIL;
					hid_t beam = CBF_H5FAIL;
					const hsize_t max[] = {H5S_UNLIMITED,4};
					const hsize_t chunk[] = {1,4};
				const hsize_t offset[] = {nx->slice,0};
					const hsize_t count[] = {1,4};
					hsize_t buf[] = {0,0};
				CBF_CALL(cbf_h5handle_require_beam(nx,&beam,0));
					CBF_CALL(cbf_H5Drequire(beam,&dset,"incident_polarisation_stokes",2,max,chunk,buf,H5T_IEEE_F64LE));
					CBF_CALL(cbf_H5Dinsert(dset,offset,0,count,buf,value,H5T_NATIVE_DOUBLE));
					cbf_H5Dfree(dset);
				}
                if (!error && have_data_esds) {
                    hid_t dset = CBF_H5FAIL;
                    hid_t beam = CBF_H5FAIL;
                    const hsize_t max[] = {H5S_UNLIMITED,4};
                    const hsize_t chunk[] = {1,4};
                    const hsize_t offset[] = {nx->slice,0};
                    const hsize_t count[] = {1,4};
                    hsize_t buf[] = {0,0};
                    CBF_CALL(cbf_h5handle_require_beam(nx,&beam,0));
                    CBF_CALL(cbf_H5Drequire(beam,&dset,"incident_polarisation_stokes_uncertainties",2,max,chunk,buf,H5T_IEEE_F64LE));
                    CBF_CALL(cbf_H5Dinsert(dset,offset,0,count,buf,value_esds,H5T_NATIVE_DOUBLE));
                    cbf_H5Dfree(dset);
			}

		}
		}
		return error;
	}

	/*
	Define a type, constructor and setters to use when processing a single row of the 'diffrn_scan_axis' table.
	*/
	typedef struct DiffrnScanAxisCache
	{
		const char * axis;
		double disp_strt;
		double angle_strt;
		double disp_incr;
		double angle_incr;
		double disp_rstrt_incr;
		double angle_rstrt_incr;
	} DiffrnScanAxisCache;
    
	static int ctor_DiffrnScanAxisCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnScanAxisCache * const c = self;
		if (!c) {
            error |= CBF_ARGUMENT;
        } else {
			c->axis = NULL;
			c->disp_strt = 0.0;
			c->angle_strt = 0.0;
			c->disp_incr = 0.0;
			c->angle_incr = 0.0;
			c->disp_rstrt_incr = 0.0;
			c->angle_rstrt_incr = 0.0;
		}
        return error;
    }

	DECL_CACHE_STR_SETTER(cache_DiffrnScanAxis_axis, DiffrnScanAxisCache, axis);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_angleIncr, DiffrnScanAxisCache, angle_incr);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_angleRstrtIncr, DiffrnScanAxisCache, angle_rstrt_incr);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_angleStrt, DiffrnScanAxisCache, angle_strt);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_dispIncr, DiffrnScanAxisCache, disp_incr);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_dispRstrtIncr, DiffrnScanAxisCache, disp_rstrt_incr);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanAxis_dispStrt, DiffrnScanAxisCache, disp_strt);
        
				/*
	Process data from a single row of 'diffrn_scan_axis'.

	For the axis with the id located in the row, locate the 'type' from the cbf file,
	the path from the 'key' object, then insert a calulated displacement or angle
	(depending on type) for the current frame. This value should be replaced by a per-
	frame value later on, if one is given, so it acts as a bit like a default value.
				*/
static int process_DiffrnScanAxisCache(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const rcache,
			 void * const tcache,
			 const unsigned int row)
	{
		int error = CBF_SUCCESS;
		DiffrnScanAxisCache * const c = rcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !c || tcache) {
			error |= CBF_ARGUMENT;
                        } else {
                    unsigned int i;
                    /* find the index of the required axis within the axis settings */
                    for (i = 0; i != key->axis.count; ++i) {
				if (!strcmp(key->axis.axis_id[i],c->axis)) {
                            break;
		}
                    }
                    /* check if I found it, if so then use it */
                    if (i == key->axis.count) {
				cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTFOUND));
                        error |= CBF_NOTFOUND;
                    } else {
				cbf_node * axis_category = NULL;
				cbf_node * axis_id_column = NULL;
				cbf_node * axis_type_column = NULL;
				const char * type = NULL;
				unsigned int row = 0;
				CBF_CALL(cbf_find_parent(&axis_category,category,CBF_DATABLOCK));
				CBF_CALL(cbf_find_child(&axis_category,axis_category,"axis"));
				CBF_CALL(cbf_find_child(&axis_id_column,axis_category,"id"));
				CBF_CALL(cbf_find_child(&axis_type_column,axis_category,"type"));
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,c->axis,&row));
				CBF_CALL(cbf_node_get_value(axis_type_column,row,&type));
                        if (CBF_SUCCESS==error) {
                            hid_t dset = CBF_H5FAIL;
					const hsize_t off[] = {nx->slice};
                            const hsize_t cnt[] = {1};
                            const hsize_t max[] = {H5S_UNLIMITED};
                            hsize_t buf[] = {0};
                            double data;
                            if (!strcmp(type,"translation")) {
						data = c->disp_strt + (c->disp_incr+c->disp_rstrt_incr)*key->frame_number;
                            } else if (!strcmp(type,"rotation")) {
						data = c->angle_strt + (c->angle_incr+c->angle_rstrt_incr)*key->frame_number;
                            } else {
                                data = 0./0.;
                            }
					CBF_CALL(cbf_H5Dfind2(nx->hfile,&dset,key->axis.path[i],1,max,buf,H5T_IEEE_F64LE));
                            CBF_CALL(cbf_H5Dinsert(dset,off,0,cnt,buf,&data,H5T_NATIVE_DOUBLE));
                            cbf_H5Dfree(dset);
                        }
                    }
                }
		return error;
	}

	/*
	Define a type, constructor and setters to use when processing a single row of the 'diffrn_scan_frame_axis' table.
	*/
	typedef struct DiffrnScanFrameAxisCache
	{
		const char * axis;
		double angle;
		double disp;
	} DiffrnScanFrameAxisCache;

	static int ctor_DiffrnScanFrameAxisCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnScanFrameAxisCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
        } else {
			c->axis = NULL;
			c->angle = 0.0;
			c->disp = 0.0;
                    }
		return error;
                }

	DECL_CACHE_STR_SETTER(cache_DiffrnScanFrameAxis_axis, DiffrnScanFrameAxisCache, axis);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanFrameAxis_angle, DiffrnScanFrameAxisCache, angle);
	DECL_CACHE_DOUBLE_SETTER(cache_DiffrnScanFrameAxis_disp, DiffrnScanFrameAxisCache, disp);

                    /*
	Process data from a single row of 'diffrn_scan_frame_axis'.

	For the axis with the id located in the row, locate the 'type' from the cbf file,
	the path from the 'key' object, then insert the displacement or angle (depending
	on type) for the current frame.
                     */
	static int process_DiffrnScanFrameAxisCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const rcache,
			 void * const tcache,
			 const unsigned int row)
	{
		int error = CBF_SUCCESS;
		DiffrnScanFrameAxisCache * const c = rcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !c || tcache) {
			error |= CBF_ARGUMENT;
                        } else {
                    unsigned int i;
                    /* find the index of the required axis within the axis settings */
                    for (i = 0; i != key->axis.count; ++i) {
				if (!strcmp(key->axis.axis_id[i],c->axis)) {
                            break;
                        }
                    }
                    /* check if I found it, if so then use it */
                    if (i == key->axis.count) {
				cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTFOUND));
                        error |= CBF_NOTFOUND;
                    } else {
				cbf_node * axis_category = NULL;
				cbf_node * axis_id_column = NULL;
				cbf_node * axis_type_column = NULL;
				const char * type = NULL;
				unsigned int row = 0;
				CBF_CALL(cbf_find_parent(&axis_category,category,CBF_DATABLOCK));
				CBF_CALL(cbf_find_child(&axis_category,axis_category,"axis"));
				CBF_CALL(cbf_find_child(&axis_id_column,axis_category,"id"));
				CBF_CALL(cbf_find_child(&axis_type_column,axis_category,"type"));
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,c->axis,&row));
				CBF_CALL(cbf_node_get_value(axis_type_column,row,&type));
                        if (CBF_SUCCESS == error) {
                            hid_t dset = CBF_H5FAIL;
					const hsize_t off[] = {nx->slice};
                            const hsize_t cnt[] = {1};
                            const hsize_t max[] = {H5S_UNLIMITED};
                            hsize_t buf[] = {0};
                            const double * data;
                            if (!strcmp(type,"translation")) {
						data = &c->disp;
                            } else if (!strcmp(type,"rotation")) {
						data = &c->angle;
                            } else {
                                data = NULL;
                            }
					CBF_CALL(cbf_H5Dfind2(nx->hfile,&dset,key->axis.path[i],1,max,buf,H5T_IEEE_F64LE));
                            CBF_CALL(cbf_H5Dinsert(dset,off,0,cnt,buf,data,H5T_NATIVE_DOUBLE));
                            cbf_H5Dfree(dset);
                        }
                    }
                }
        return error;
    }

	/*
	Define a type, constructor, destructor and setters to use when accumulating data from rows of the
	'diffrn_detector_axis' table and when processing that data after all of it has been acquired.
	*/
	typedef struct DiffrnDetectorAxisTCache
    {
		size_t count;
		const char * * axis_id;
		unsigned int * in_degree;
		const char * * path;
	} DiffrnDetectorAxisTCache;
        
	static int ctor_DiffrnDetectorAxisTCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnDetectorAxisTCache * const c = self;
		if (!c) {
            error |= CBF_ARGUMENT;
        } else {
			c->count = 0;
			c->axis_id = NULL;
			c->in_degree = NULL;
			c->path = NULL;
                    }
		return error;
                }

	static int dtor_DiffrnDetectorAxisTCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnDetectorAxisTCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
            } else {
			size_t i;
			for (i = 0; i != c->count; ++i) free((void*)c->path[i]);
			free((void*)c->axis_id);
			free((void*)c->in_degree);
			free((void*)c->path);
            }
		return error;
	}

            /*
	A utility function to simplify usage of the 'DiffrnDetectorAxisTCache' object.
             */
	static int DiffrnDetectorAxisTCache_insert_axis
			(DiffrnDetectorAxisTCache * const c,
			 const char * const axis_id,
			 const char * const path)
                {
		int error = CBF_SUCCESS;
		if (!c) {
			error |= CBF_ARGUMENT;
		} else {
			const char * * new_axis_id = realloc(c->axis_id,(1+c->count)*sizeof(char*));
			unsigned int * new_in_degree = realloc(c->in_degree,(1+c->count)*sizeof(unsigned int));
			const char * * new_path = realloc(c->path,(1+c->count)*sizeof(char*));
			if (!new_axis_id) {
				error |= CBF_ALLOC;
			} else {
				c->axis_id = new_axis_id;
				}
			if (!new_in_degree) {
				error |= CBF_ALLOC;
                    } else {
				c->in_degree = new_in_degree;
                    }
			if (!new_path) {
				error |= CBF_ALLOC;
                    } else {
				c->path = new_path;
					}
			if (!error) {
				c->axis_id[c->count] = axis_id;
				c->in_degree[c->count] = 0;
				c->path[c->count] = path;
				++c->count;
				}
			}
		return error;
		}

            /*
	Process data accumulated from all matching rows of 'diffrn_detector_axis'.

	This searches for a single leaf axis in the extracted set of axes, then writes the
	detector dependency in nexus, and traverses the dependency chain for it to add each
	required axis to the 'key' object with any relevant paths which were generated
	when extracting data from each individual row of 'diffrn_detector_axis'.
             */
	static int process_DiffrnDetectorAxisTCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const tcache)
	{
		int error = CBF_SUCCESS;
		DiffrnDetectorAxisTCache * const c = tcache;
		if (!category || !nx || !key || !c) {
			cbf_debug_print("error: can't process data from 'diffrn_detector_axis' table.");
			error |= CBF_ARGUMENT;
		} else {
            /*
             I now have all relevant axes from this category, so I can find & write the dependency for the detector.
             New axes are in the cache object. For each axis I need to set an in_degree, which tells me how many axes
             refer to this axis. An in_degree of 0 means I probably have a leaf, a check to ensure only one axis has
             an in_degree of 0 exists in the subset is needed to ensure I have a single valid leaf axis. If I have a
             valid leaf then I can write the detector's dependency and add that and all it's dependent axes to the key
             for later conversion.
             */
            unsigned int i;
			unsigned int leaf = c->count;
            unsigned int leaves = 0;
			cbf_node * axis_category = NULL;
			cbf_node * axis_id_column = NULL;
            cbf_node * axis_depends_on_column = NULL;
            cbf_node * axis_rotation_axis_column = NULL;
			CBF_CALL(cbf_find_parent(&axis_category,category,CBF_DATABLOCK));
			CBF_CALL(cbf_find_child(&axis_category,axis_category,"axis"));
			CBF_CALL(cbf_find_child(&axis_id_column,axis_category,"id"));
            if (cbf_find_child(&axis_depends_on_column,axis_category,"depends_on")) {
                axis_depends_on_column = NULL;
            };
            if (cbf_find_child(&axis_rotation_axis_column,axis_category,"rotation_axis")) {
                axis_rotation_axis_column = NULL;
            };
			/* populate the in-degree field in the cached data */
			for (i = 0; c->count != i; ++i) {
				unsigned int row = 0;
                const char * depends_on = NULL;
                /* locate the current axis and get its dependency */
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,c->axis_id[i],&row));
                if (axis_depends_on_column) {
                    CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&depends_on));
                    if (CBF_SUCCESS==error) {
                        unsigned int j;
                        /* I know which axis the current axis depends on, look for it in the current subset */
                        for (j = 0; c->count != j; ++j) {
                            if (!cbf_cistrcmp(c->axis_id[j],depends_on)) break;
                        }
                        if (c->count != j) {
                            ++c->in_degree[j];
                        }
                    }
                }
            }
            /* ensure there is only one leaf, and find it */
			for (i = 0; c->count != i; ++i) {
				if (0==c->in_degree[i]) {
                    leaf = i;
                    ++leaves;
                }
            }
            /* test if a single valid leaf axis was found */
			if (1!=leaves || leaf>=c->count) {
				cbf_debug_print("error: couldn't determine what defines the detector orientation");
                error |= CBF_FORMAT;
            } else {
				unsigned int row = 0;
				unsigned int prev_idx = key->axis.count;
				const char * axis_id = c->axis_id[leaf];
				size_t index;
				/* I now have a valid leaf axis, write the dependency... */
				CBF_CALL(cbf_H5Drequire_flstring(nx->nxdetectors[nx->cur_detector],0,"depends_on",c->path[leaf]));
				/* ...record the leaf axis in the key... */
				if ((error|=_cbf_insert_axis(&key->axis,axis_id,c->path[leaf]))) {
					cbf_debug_print2("error: %s\n",cbf_strerror(error));
				} else {
					c->path[leaf] = NULL;
                }
				/* ...find the next axis to look for... */
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,axis_id,&row));
                CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
				/* ...and log all dependent axes in the key, taking paths from the cache when possible. */
				while (axis_id && strcmp(axis_id,".") && !error) {
					/* search for an axis with an id given by axis_id in the key, the cache, then the cbf file. */
					if (!find_index_of_str_in_array(key->axis.axis_id,key->axis.count,axis_id,&index)) {
						/* I already have the axis in the key, so I don't need to process any more axes. */
						key->axis.depends_on[prev_idx] = index;
						break;
					} else if (!find_index_of_str_in_array(c->axis_id,c->count,axis_id,&index)) {
						const unsigned int idx = key->axis.count;
						/* I have a match in the cache - re-use its path. */
						if ((error|=_cbf_insert_axis(&key->axis,axis_id,c->path[index]))) {
							cbf_debug_print2("error: %s\n",cbf_strerror(error));
						} else {
							/* give up ownership of the path */
							c->path[index] = NULL;
							/* set dependency indices */
							key->axis.depends_on[prev_idx] = idx;
							prev_idx = idx;
							/* look up the next axis to process */
							CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,axis_id,&row));
                            CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
                        }
					} else if (!(error|=cbf_node_find_nextrow(axis_id_column,0,axis_id,&row))) {
						const unsigned int idx = key->axis.count;
						/* No match found in the key or cache, found one in the axes in the cbf file. */
						if ((error|=_cbf_insert_axis(&key->axis,axis_id,NULL))) {
							cbf_debug_print2("error: %s\n",cbf_strerror(error));
						} else {
							key->axis.depends_on[prev_idx] = idx;
							prev_idx = idx;
                        }
                        CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
                    } else {
						/* it appears that the expected axis doesn't exist, this is an error */
						cbf_debug_print3("error: %s %s\n","No axis found for axis with axis_id:",axis_id);
						error |= CBF_NOTFOUND;
                    }
                }
            }
        }
		return error;
	}

            /*
	Define a type, constructor and setters to use when processing a single row of the 'diffrn_detector_axis' table.
             */
	typedef struct DiffrnDetectorAxisRCache
    {
		const char * axis;
	} DiffrnDetectorAxisRCache;

	static int ctor_DiffrnDetectorAxisRCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnDetectorAxisRCache * const c = self;
		if (!c) {
            error |= CBF_ARGUMENT;
        } else {
			c->axis = NULL;
				}
		return error;
			}

	DECL_CACHE_STR_SETTER(cache_DiffrnDetectorAxis_axis, DiffrnDetectorAxisRCache, axis);

                    /*
	Process data from a single row of 'diffrn_detector_axis'.

	This generates a path for the axis that was found and inserts it into the table-level cache for further processing.
                     */
	static int process_DiffrnDetectorAxisRCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const rcache,
			 void * const tcache,
			 const unsigned int row)
    {
		int error = CBF_SUCCESS;
		DiffrnDetectorAxisRCache * const r = rcache;
		DiffrnDetectorAxisTCache * const t = tcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !r || !t) {
			cbf_debug_print("error: can't process row of 'diffrn_detector_axis'.");
			error |= CBF_ARGUMENT;
        } else {
			if (!r->axis) {
				cbf_debug_print("error: 'axis_id' not found");
                error |= CBF_NOTFOUND;
            } else {
                const char * axis_path;
                const char * taxis_path;

                /* the axis exists - convert the data */
				hid_t det = CBF_H5FAIL;
                hid_t axisGroup = CBF_H5FAIL;
                const char axis_group_name[] = "transformations";
                if (cbf_get_NX_axis_path(nx,r->axis,&taxis_path)) {
                    CBF_CALL(cbf_h5handle_require_detector(nx,&det,0));
                    CBF_CALL(cbf_H5Grequire(det,&axisGroup,axis_group_name));
                    CBF_CALL(cbf_H5Arequire_string(axisGroup,"NX_class","NXtransformations"));
                    if (!error) {
                        const char path_empty[] = "";
                        const char * path_parts[] = {
                            path_empty,
                            nx->nxid_name,
                            nx->nxinstrument_name,
                            nx->nxdetector_names[nx->cur_detector],
                            axis_group_name,
                            r->axis,
                            0 };
                        axis_path = _cbf_strjoin(path_parts,'/');
                        /* try to transfer ownership of the path to the table-level cache */
                        if ((error|=DiffrnDetectorAxisTCache_insert_axis(t,r->axis,axis_path))) {
                            cbf_debug_print2("error: %s\n",cbf_strerror(error));
                        } else {
                            axis_path = NULL;
                        }
                        free((void*)axis_path);
                    }
                } else {
                    axis_path = _cbf_strdup(taxis_path);
                    cbf_debug_print3("Mapped axis path for axis '%s' to '%s'\n",r->axis,axis_path);
                    /* try to transfer ownership of the path to the table-level cache */
                    if ((error|=DiffrnDetectorAxisTCache_insert_axis(t,r->axis,axis_path))) {
                        cbf_debug_print2("error: %s\n",cbf_strerror(error));
                    } else {
                        axis_path = NULL;
                    }
                    free((void*)axis_path);
                }
				cbf_H5Gfree(axisGroup);
			}
		}
		return error;
	}

                        /*
	Define a type, constructor, destructor and setters to use when accumulating data from rows of the
	'diffrn_measurement_axis' table and when processing that data after all of it has been acquired.
                         */
	typedef struct DiffrnMeasurementAxisTCache
	{
		size_t count;
		const char * * axis_id;
		unsigned int * in_degree;
		const char * * path;
	} DiffrnMeasurementAxisTCache;

	static int ctor_DiffrnMeasurementAxisTCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnMeasurementAxisTCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
		} else {
			c->count = 0;
			c->axis_id = NULL;
			c->in_degree = NULL;
			c->path = NULL;
					}
		return error;
				}

	static int dtor_DiffrnMeasurementAxisTCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnMeasurementAxisTCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
		} else {
			size_t i;
			for (i = 0; i != c->count; ++i) free((void*)c->path[i]);
			free((void*)c->axis_id);
			free((void*)c->in_degree);
			free((void*)c->path);
			}
		return error;
		}

            /*
	A utility function to simplify usage of the 'DiffrnMeasurementAxisTCache' object.
             */
	static int DiffrnMeasurementAxisTCache_insert_axis
			(DiffrnMeasurementAxisTCache * const c,
			 const char * const axis_id,
			 const char * const path)
	{
		int error = CBF_SUCCESS;
		if (!c) {
			error |= CBF_ARGUMENT;
            } else {
			const char * * new_axis_id = realloc(c->axis_id,(1+c->count)*sizeof(char*));
			unsigned int * new_in_degree = realloc(c->in_degree,(1+c->count)*sizeof(unsigned int));
			const char * * new_path = realloc(c->path,(1+c->count)*sizeof(char*));
			if (!new_axis_id) {
				error |= CBF_ALLOC;
			} else {
				c->axis_id = new_axis_id;
			}
			if (!new_in_degree) {
				error |= CBF_ALLOC;
			} else {
				c->in_degree = new_in_degree;
			}
			if (!new_path) {
				error |= CBF_ALLOC;
			} else {
				c->path = new_path;
			}
			if (!error) {
				c->axis_id[c->count] = axis_id;
				c->in_degree[c->count] = 0;
				c->path[c->count] = path;
				++c->count;
			}
		}
		return error;
	}

	/*
	Process data accumulated from all matching rows of 'diffrn_measurement_axis'.

	This searches for a single leaf axis in the extracted set of axes, then writes the
	sample dependency in nexus, and traverses the dependency chain for it to add each
	required axis to the 'key' object with any relevant paths which were generated
	when extracting data from each individual row of 'diffrn_measurement_axis'.
	*/
	static int process_DiffrnMeasurementAxisTCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const tcache)
	{
		int error = CBF_SUCCESS;
		DiffrnMeasurementAxisTCache * const c = tcache;
		if (!category || !nx || !key || !c) {
			cbf_debug_print("error: can't process data from 'diffrn_measurement_axis' table.");
			error |= CBF_ARGUMENT;
		} else {
				/*
             I now have all relevant axes from this category, so I can find & write the dependency for the sample.
			New axes are in the cache object. For each axis I need to set an in_degree, which tells me how many axes
			refer to this axis. An in_degree of 0 means I probably have a leaf, a check to ensure only one axis has
			an in_degree of 0 exists in the subset is needed to ensure I have a single valid leaf axis. If I have a
			valid leaf then I can write the sample's dependency and add that and all it's dependent axes to the key
			for later conversion.
             */
                unsigned int i;
			unsigned int leaf = c->count;
                unsigned int leaves = 0;
			cbf_node * axis_category = NULL;
			cbf_node * axis_id_column = NULL;
            cbf_node * axis_depends_on_column = NULL;
			CBF_CALL(cbf_find_parent(&axis_category,category,CBF_DATABLOCK));
			CBF_CALL(cbf_find_child(&axis_category,axis_category,"axis"));
			CBF_CALL(cbf_find_child(&axis_id_column,axis_category,"id"));
            CBF_CALL(cbf_find_child(&axis_depends_on_column,axis_category,"depends_on"));
			/* populate the in-degree field in the cached data */
			for (i = 0; c->count != i; ++i) {
				unsigned int row = 0;
                    const char * depends_on = NULL;
                /* locate the current axis and get its dependency */
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,c->axis_id[i],&row));
                CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&depends_on));
		if (CBF_SUCCESS == error) {
                        unsigned int j;
                        /* I know which axis the current axis depends on, look for it in the current subset */
					for (j = 0; c->count != j; ++j) {
						if (!cbf_cistrcmp(c->axis_id[j],depends_on)) break;
			}
					if (c->count != j) {
						++c->in_degree[j];
			}
		}
                }
                /* ensure there is only one leaf, and find it */
			for (i = 0; c->count != i; ++i) {
				if (0==c->in_degree[i]) {
                        leaf = i;
                        ++leaves;
                    }
                }
                /* test if a single valid leaf axis was found */
			if (1!=leaves || leaf>=c->count) {
				/* it *might* be possible to use multiple goniometers, so a different check might be required here */
				cbf_debug_print("error: couldn't determine what defines the sample orientation");
                    error |= CBF_FORMAT;
                } else {
				unsigned int row = 0;
				unsigned int prev_idx = key->axis.count;
				const char * axis_id = c->axis_id[leaf];
				size_t index;
				/* I now have a valid leaf axis, write the dependency... */
				CBF_CALL(cbf_H5Drequire_flstring(nx->nxsample,0,"depends_on",c->path[leaf]));
				/* ...record the leaf axis in the key... */
				if ((error|=_cbf_insert_axis(&key->axis,axis_id,c->path[leaf]))) {
					cbf_debug_print2("error: %s\n",cbf_strerror(error));
				} else {
					c->path[leaf] = NULL;
                }
				/* ...find the next axis to look for... */
				CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,axis_id,&row));
                CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
				/* ...and log all dependent axes in the key, taking paths from the cache when possible. */
				while (axis_id && strcmp(axis_id,".") && !error) {
					/* search for an axis with an id given by axis_id in the key, the cache, then the cbf file. */
					if (!find_index_of_str_in_array(key->axis.axis_id,key->axis.count,axis_id,&index)) {
						/* I already have the axis in the key, so I don't need to process any more axes. */
						key->axis.depends_on[prev_idx] = index;
						break;
					} else if (!find_index_of_str_in_array(c->axis_id,c->count,axis_id,&index)) {
						const unsigned int idx = key->axis.count;
						/* I have a match in the cache - re-use its path. */
						if ((error|=_cbf_insert_axis(&key->axis,axis_id,c->path[index]))) {
							cbf_debug_print2("error: %s\n",cbf_strerror(error));
						} else {
							/* give up ownership of the path */
							c->path[index] = NULL;
							/* set dependency indices */
							key->axis.depends_on[prev_idx] = idx;
							prev_idx = idx;
							/* look up the next axis to process */
							CBF_CALL(cbf_node_find_nextrow(axis_id_column,0,axis_id,&row));
                            CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
            }
					} else if (!(error|=cbf_node_find_nextrow(axis_id_column,0,axis_id,&row))) {
						const unsigned int idx = key->axis.count;
						/* No match found in the key or cache, found one in the axes in the cbf file. */
						if ((error|=_cbf_insert_axis(&key->axis,axis_id,NULL))) {
							cbf_debug_print2("error: %s\n",cbf_strerror(error));
						} else {
							key->axis.depends_on[prev_idx] = idx;
							prev_idx = idx;
        }
                        CBF_CALL(cbf_node_get_value(axis_depends_on_column,row,&axis_id));
					} else {
						/* it appears that the expected axis doesn't exist, this is an error */
						cbf_debug_print3("error: %s %s\n","No axis found for axis with axis_id:", axis_id);
						error |= CBF_NOTFOUND;
					}
				}
			}
		}
		return error;
	}

	/*
	Define a type, constructor and setters to use when processing a single row of the 'diffrn_measurement_axis' table.
	*/
	typedef struct DiffrnMeasurementAxisRCache
	{
		const char * axis;
		/* insert data to identify different goniometers here? */
	} DiffrnMeasurementAxisRCache;

	static int ctor_DiffrnMeasurementAxisRCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		DiffrnMeasurementAxisRCache * const c = self;
		if (!c) {
            error |= CBF_ARGUMENT;
        } else {
			c->axis = NULL;
		}
		return error;
		}

	DECL_CACHE_STR_SETTER(cache_DiffrnMeasurementAxis_axis, DiffrnMeasurementAxisRCache, axis);

            /*
	Process data from a single row of 'diffrn_measurement_axis'.

	This generates a path for the axis that was found and inserts it into the table-level cache for further processing.
             */
	static int process_DiffrnMeasurementAxisRCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const rcache,
			 void * const tcache,
			 const unsigned int row)
                {
		int error = CBF_SUCCESS;
		DiffrnMeasurementAxisRCache * const r = rcache;
		DiffrnMeasurementAxisTCache * const t = tcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !r || !t) {
			cbf_debug_print("error: can't process row of 'diffrn_measurement_axis'.");
			error |= CBF_ARGUMENT;
		} else {
			if (!r->axis) {
				cbf_debug_print("error: 'axis_id' not found");
				error |= CBF_NOTFOUND;
			} else {
                const char * axis_path;
                const char * taxis_path;
                
				/* the axis exists - convert the data */
				hid_t sample = CBF_H5FAIL;
				hid_t axisGroup = CBF_H5FAIL;
                const char axis_group_name[] = "transformations";
                if (cbf_get_NX_axis_path(nx,r->axis,&taxis_path)) {
                    CBF_CALL(cbf_h5handle_require_sample(nx,&sample,0));
                    CBF_CALL(cbf_H5Grequire(sample,&axisGroup,axis_group_name));
                    CBF_CALL(cbf_H5Arequire_string(axisGroup,"NX_class","NXtransformations"));
                    if (!error) {
                        const char path_empty[] = "";
                        const char * path_parts[] = {
                            path_empty,
                            nx->nxid_name,
                            nx->nxsample_name,
                            axis_group_name,
                            r->axis,
                            0
                        };
                        axis_path = _cbf_strjoin(path_parts,'/');
                        /* try to transfer ownership of the path to the table-level cache */
                        if ((error|=DiffrnMeasurementAxisTCache_insert_axis(t,r->axis,axis_path))) {
                            cbf_debug_print2("error: %s\n",cbf_strerror(error));
                        } else {
                            axis_path = NULL;
                        }
                        free((void*)axis_path);
                    }
                } else {
                    axis_path = _cbf_strdup(taxis_path);
                    cbf_debug_print3("Mapped axis path for axis '%s' to '%s'\n",r->axis,axis_path);
                    /* try to transfer ownership of the path to the table-level cache */
                    if ((error|=DiffrnMeasurementAxisTCache_insert_axis(t,r->axis,axis_path))) {
                        cbf_debug_print2("error: %s\n",cbf_strerror(error));
                    } else {
                        axis_path = NULL;
                    }
                    free((void*)axis_path);

                }
				cbf_H5Gfree(axisGroup);
            }
                    }
		return error;
	}

                    /*
	Define a type, constructor and setters to use when processing a single row of the 'array_intensities' table.
                     */
	typedef struct ArrayIntensitiesCache
	{
		const char * linearity;
		double gain;
		double offset;
		double scaling;
	} ArrayIntensitiesCache;

	static int ctor_ArrayIntensitiesCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		ArrayIntensitiesCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
                    } else {
			c->linearity = NULL;
			c->gain = 0.0;
			c->offset = 0.0;
			c->scaling = 0.0;
                    }
		return error;
	}

	DECL_CACHE_STR_SETTER(cache_ArrayIntensities_linearity, ArrayIntensitiesCache, linearity);
	DECL_CACHE_DOUBLE_SETTER(cache_ArrayIntensities_gain, ArrayIntensitiesCache, gain);
	DECL_CACHE_DOUBLE_SETTER(cache_ArrayIntensities_offset, ArrayIntensitiesCache, offset);
	DECL_CACHE_DOUBLE_SETTER(cache_ArrayIntensities_scaling, ArrayIntensitiesCache, scaling);

	/*
	Process data from a single row of 'array_intensities'.

	The processing depends on the value of 'linearity':
	if linearity is "linear" then the scaling factor is assumed to be 1/gain.
	if linearity in ["linear","offset","scaling","scaling_offset"]:
	write the 'offset' and 'scaling_factor' to datasets with those names
	elseif linearity in ["sqrt_scaled","logarithmic_scaled"]:
	throw Exception("Non-linear scaling is not supported in NeXus")
	elseif linearity is "raw" then no scaling information needs to be stored for this row
	else throw Exception("Unrecognised linearity")
	*/
	static int process_ArrayIntensitiesCache
                    (cbf_node * const category,
                     cbf_h5handle nx,
                     cbf_cbf2nx_key_t * const key,
                     void * const rcache,
                     void * const tcache,
                     const unsigned int row)
	{
		int error = CBF_SUCCESS;
		ArrayIntensitiesCache * const c = rcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !c || tcache) {
            error |= CBF_ARGUMENT;
        } else {
				/*
			I have extracted all the information from a relevant row,
			now I need to convert it to nexus format and write it.
				*/
			if (!c->linearity) {
				cbf_debug_print("error: 'array_intensities.linearity' not found");
				error |= CBF_NOTFOUND;
			} else {
				hsize_t max[] = {H5S_UNLIMITED};
				hsize_t cnk[] = {1};
				hsize_t buf[] = {0};
				hsize_t data_offset[] = {nx->slice};
				hsize_t count[] = {1};
				if (!cbf_cistrcmp(c->linearity,"linear")) c->scaling = 1.0/c->gain;
				if (!cbf_cistrcmp(c->linearity,"linear") || !cbf_cistrcmp(c->linearity,"offset") || !cbf_cistrcmp(c->linearity,"scaling") || !cbf_cistrcmp(c->linearity,"scaling_offset")) {
					hid_t dset_offset = CBF_H5FAIL;
					hid_t dset_scale = CBF_H5FAIL;
					CBF_CALL(cbf_H5Drequire(nx->nxdetectors[nx->cur_detector],&dset_offset,"offset",1,max,cnk,buf,H5T_IEEE_F64LE));
					CBF_CALL(cbf_H5Dinsert(dset_offset,data_offset,0,count,buf,&c->offset,H5T_NATIVE_DOUBLE));
					CBF_CALL(cbf_H5Drequire(nx->nxdetectors[nx->cur_detector],&dset_scale,"scaling_factor",1,max,cnk,buf,H5T_IEEE_F64LE));
					CBF_CALL(cbf_H5Dinsert(dset_scale,data_offset,0,count,buf,&c->scaling,H5T_NATIVE_DOUBLE));
					cbf_H5Dfree(dset_offset);
					cbf_H5Dfree(dset_scale);
				} else if (!cbf_cistrcmp(c->linearity,"raw")) {
					/* no-op! */
				} else if (!cbf_cistrcmp(c->linearity,"sqrt_scaled") || !cbf_cistrcmp(c->linearity,"logarithmic_scaled")) {
					cbf_debug_print3("error: %s %s\n","unsupported 'array_intensities.linearity' value:",c->linearity);
				} else {
					cbf_debug_print3("error: %s %s\n","unrecognised 'array_intensities.linearity' value:",c->linearity);
					error |= CBF_FORMAT;
		}
		}
		}
		return error;
            }

            /*
	Define a type, constructor and setters to use when processing a single row of the 'array_structure_list' table.
             */
	typedef struct ArrayStructureListCache
                {
		const char * axis_set_id;
		const char * direction;
		unsigned int dimension;
		unsigned int index;
		unsigned int precedence;
	} ArrayStructureListCache;

	static int ctor_ArrayStructureListCache
			(void * const self)
	{
		int error = CBF_SUCCESS;
		ArrayStructureListCache * const c = self;
		if (!c) {
			error |= CBF_ARGUMENT;
		} else {
			c->axis_set_id = NULL;
			c->direction = NULL;
			c->dimension = 0;
			c->index = 0;
			c->precedence = 0;
                        }
		return error;
                    }

	DECL_CACHE_STR_SETTER(cache_ArrayStructureList_axis_set_id, ArrayStructureListCache, axis_set_id);
	DECL_CACHE_STR_SETTER(cache_ArrayStructureList_direction, ArrayStructureListCache, direction);
	DECL_CACHE_UINT_SETTER(cache_ArrayStructureList_dimension, ArrayStructureListCache, dimension);
	DECL_CACHE_UINT_SETTER(cache_ArrayStructureList_index, ArrayStructureListCache, index);
	DECL_CACHE_UINT_SETTER(cache_ArrayStructureList_precedence, ArrayStructureListCache, precedence);

                    /*
	Process data from a single row of 'array_structure_list'.

	Picks a name for the axis set based on its precedence, constructs a path for it and then caches
	that data in the given 'key'.
                     */
	static int process_ArrayStructureListCache
			(cbf_node * const category,
			 cbf_h5handle nx,
			 cbf_cbf2nx_key_t * const key,
			 void * const rcache,
			 void * const tcache,
			 const unsigned int row)
	{
		int error = CBF_SUCCESS;
		ArrayStructureListCache * const c = rcache;
		CBF_UNUSED(row);
		if (!category || !nx || !key || !c || tcache) {
			error |= CBF_ARGUMENT;
                    } else {
			const char empty_string[] = "";
			const char pixel_y[] = "y_pixel_offset";
			const char pixel_x[] = "x_pixel_offset";
			const char * const axis_names[] = {empty_string, pixel_x, pixel_y};
			if (c->precedence < 1 || c->precedence > 2) {
				/* I don't have axis names defined outside of this range */
				cbf_debug_print("error: 'precedence' isn't in the range of valid values");
				error |= CBF_FORMAT;
			} else {
                const char * axis_path;
                const char * taxis_path;
                
                if (cbf_get_NX_axis_path(nx,axis_names[c->precedence],&taxis_path)){
				CBF_CALL(cbf_h5handle_require_detector(nx,0,0));
				if (!error) {
					const char * path_parts[] = {
						empty_string,
						nx->nxid_name,
						nx->nxinstrument_name,
						nx->nxdetector_names[nx->cur_detector],
						/* select the correct axis name */
						axis_names[c->precedence],
						0
					};
                        axis_path = _cbf_strjoin(path_parts,'/');
					CBF_CALL(
							_cbf_insert_arrayAxisSet(
							&key->arrayAxisSet,
					c->axis_set_id,
					axis_path,
					c->index,
					c->precedence,
					c->dimension,
					c->direction
													)
							);
					free((void*)axis_path);
                    }
                } else {
                    axis_path = _cbf_strdup(taxis_path);
                    cbf_debug_print3("Mapped axis path for axis '%s' to '%s'\n",axis_names[c->precedence],axis_path);
                    /* try to transfer ownership of the path to the table-level cache */
                    CBF_CALL(
                             _cbf_insert_arrayAxisSet(
                                                      &key->arrayAxisSet,
                                                      c->axis_set_id,
                                                      axis_path,
                                                      c->index,
                                                      c->precedence,
                                                      c->dimension,
                                                      c->direction
                                                      )
                             );
                    free((void*)axis_path);
                }
            }
        }
		return error;
	}

        /*
	Extract a fixed-length string value from 'column[row]', apply an optional
	filter found in 'conv' and store it in 'nx'. The group, field name and format of the
	data in 'nx' is found in 'conv'.
         */
	static int cbf_convert_cbf2nx_flstr
			(cbf_node * const column,
			 const unsigned int row,
			 cbf_h5handle nx,
			 const cbf2nx_item_datamap_t * conv)
	{
		int error = CBF_SUCCESS;
		if (!column) {
			cbf_debug_print("error: invalid column given");
            error |= CBF_ARGUMENT;
		} else if (row >= column->children) {
			cbf_debug_print("error: invalid row given");
            error |= CBF_ARGUMENT;
		} else if (!nx) {
			cbf_debug_print("error: invalid hdf5 handle given");
            error |= CBF_ARGUMENT;
		} else if (!conv) {
			cbf_debug_print("error: invalid conversion data given");
			error |= CBF_ARGUMENT;
            } else {
			hid_t obj = CBF_H5FAIL;
			hid_t dset = CBF_H5FAIL;
			const char * in = NULL;
			const char * _out = NULL;
			const char * out = NULL;
			CBF_CALL(conv->get_object(nx,&obj,NULL));
			CBF_CALL(cbf_node_get_value(column, row, &in));
			if (conv->filter) {
				filter_string_func filter = (filter_string_func)(conv->filter);
				CBF_CALL(filter(in,&_out));
				out = _out;
        } else {
				out = in;
		}
			if (0 != conv->rank) {
				cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTIMPLEMENTED));
				error |= CBF_NOTIMPLEMENTED;
		}
			CBF_CALL(cbf_H5Drequire_flstring(obj,&dset,conv->name,out));
			if (conv->units) CBF_CALL(cbf_H5Arequire_string(dset,"units",conv->units));
			cbf_H5Dfree(dset);
			free((void*)_out);
            }
		return error;
            }

            /*
	Extract a variable-length string value from 'column[row]', apply an optional
	filter found in 'conv' and store it in 'nx'. The group, field name and format of the
	data in 'nx' is found in 'conv'.
             */
	static int cbf_convert_cbf2nx_vlstr
			(cbf_node * const column,
			 const unsigned int row,
			 cbf_h5handle nx,
			 const cbf2nx_item_datamap_t * const conv)
                {
		int error = CBF_SUCCESS;
		if (!column) {
			cbf_debug_print2("error: %s\n","invalid column given");
			error |= CBF_ARGUMENT;
		} else if (row >= column->children) {
			cbf_debug_print2("error: %s\n","invalid row given");
			error |= CBF_ARGUMENT;
		} else if (!nx) {
			cbf_debug_print2("error: %s\n","invalid hdf5 handle given");
			error |= CBF_ARGUMENT;
		} else if (!conv) {
			cbf_debug_print2("error: %s\n","invalid conversion data given");
			error |= CBF_ARGUMENT;
		} else {
			hid_t obj = CBF_H5FAIL;
			hid_t dset = CBF_H5FAIL;
			hid_t vlstr = CBF_H5FAIL;
			const char * in = NULL;
			const char * _out = NULL;
			const char * out = NULL;
			CBF_CALL(conv->get_object(nx,&obj,NULL));
			CBF_CALL(cbf_H5Tcreate_string(&vlstr,H5T_VARIABLE));
			CBF_CALL(cbf_node_get_value(column, row, &in));
			if (conv->filter) {
				filter_string_func filter = (filter_string_func)(conv->filter);
				CBF_CALL(filter(in,&_out));
				out = _out;
			} else {
				out = in;
                        }
			if (0==conv->rank) {
				CBF_CALL(cbf_H5Drequire(obj,&dset,conv->name,0,NULL,NULL,NULL,vlstr));
				CBF_CALL(cbf_H5Dwrite2(dset,NULL,NULL,NULL,&out,vlstr));
			} else if (1==conv->rank) {
				const hsize_t max[] = {H5S_UNLIMITED};
				const hsize_t cnk[] = {1};
				const hsize_t off[] = {nx->slice};
				const hsize_t cnt[] = {1};
				hsize_t buf[] = {0};
				CBF_CALL(cbf_H5Drequire(obj,&dset,conv->name,1,max,cnk,buf,vlstr));
				CBF_CALL(cbf_H5Dinsert(dset,off,NULL,cnt,buf,&out,vlstr));
			} else {
				cbf_debug_print("error: unrecognised/not implemented data rank");
                    }
			if (conv->units) CBF_CALL(cbf_H5Arequire_string(dset,"units",conv->units));
			cbf_H5Dfree(dset);
			cbf_H5Tfree(vlstr);
			free((void*)_out);
                }
		return error;
                    }

                    /*
	Extract a double-precision floating-point value from 'column[row]', apply an optional
	filter found in 'conv' and store it in 'nx'. The group, field name and format of the
	data in 'nx' is found in 'conv'.
                     */
	static int cbf_convert_cbf2nx_double
			(cbf_node * const column,
			 const unsigned int row,
			 cbf_h5handle nx,
			 const cbf2nx_item_datamap_t * conv)
                    {
		int error = CBF_SUCCESS;
		if (!column) {
			cbf_debug_print("error: invalid column given");
			error |= CBF_ARGUMENT;
		} else if (row >= column->children) {
			cbf_debug_print("error: invalid row given");
			error |= CBF_ARGUMENT;
		} else if (!nx) {
			cbf_debug_print("error: invalid hdf5 handle given");
			error |= CBF_ARGUMENT;
		} else if (!conv) {
			cbf_debug_print("error: invalid conversion data given");
			error |= CBF_ARGUMENT;
		} else {
			hid_t obj = CBF_H5FAIL;
#ifdef CBF_USE_ULP
			cmp_double_param_t cmp_double_params;
			void * cmp_params = &cmp_double_params;
			/* set up the comparison parameters */
			cmp_double_params.cmp_double_as_float = cbf_has_ULP64() ? nx->cmp_double_as_float : 1;
			cmp_double_params.ulp32 = nx->float_ulp;
#ifndef NO_UINT64_TYPE
			cmp_double_params.ulp64 = nx->double_ulp;
#endif
#else
			void * cmp_params = 0;
            CBF_UNUSED(cmp_params);
#endif
			/* it looks like I might be able to convert the data */
			CBF_CALL(conv->get_object(nx,&obj,NULL));
			double in = 0., out = 0.;
			hid_t dset = CBF_H5FAIL;
			CBF_CALL(cbf_node_get_doublevalue(column, row, &in));
			if (conv->filter) {
				filter_double_func filter = (filter_double_func)(conv->filter);
				CBF_CALL(filter(in,&out));
			} else {
				out = in;
                        }
			if (0==conv->rank) {
				CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(obj,&dset,conv->name,out,cmp_double,cmp_params));
			} else if (1==conv->rank) {
				const hsize_t max[] = {H5S_UNLIMITED};
				const hsize_t cnk[] = {1};
				const hsize_t off[] = {nx->slice};
				const hsize_t cnt[] = {1};
				hsize_t buf[] = {0};
				CBF_CALL(cbf_H5Drequire(obj,&dset,conv->name,1,max,cnk,buf,H5T_IEEE_F64LE));
				CBF_CALL(cbf_H5Dinsert(dset,off,NULL,cnt,buf,&out,H5T_NATIVE_DOUBLE));
                    } else {
				cbf_debug_print("error: unrecognised/not implemented data rank");
                    }
			if (conv->units) CBF_CALL(cbf_H5Arequire_string(dset,"units",conv->units));
			cbf_H5Dfree(dset);
                }
		return error;
	}

    /*
     Convert two strings to integers and compare them for equality.
     If one can't be converted then the most negative representable value should be returned,
     instead of any value near zero.
	Used to compare binary id values for equality.
     */
    static int strintcmp
    (const char * const s1,
     const char * const s2)
    {
        if (!s1 || !s2) {
            return INT_MIN;
        } else {
            char * s1_end = NULL;
            char * s2_end = NULL;
            const int s1_int = strtol(s1,&s1_end,0);
            const int s2_int = strtol(s2,&s2_end,0);
            if (s1==s1_end || s2==s2_end) {
                return INT_MIN;
            } else {
                return s1_int-s2_int;
            }
        }
    }
    
	static cbf_primary_key_t array_data_key[] = {
		{"array_id",cbf2nx_key_get_array_id,strcmp},
		{"binary_id",cbf2nx_key_get_binary_id,strintcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t array_data_map[] = {
		{"data",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayData_data}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t array_intensities_key[] = {
		{"array_id",cbf2nx_key_get_array_id,strcmp},
		{"binary_id",cbf2nx_key_get_binary_id,strintcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t array_intensities_map[] = {
		{"gain",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayIntensities_gain}}},
		{"linearity",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayIntensities_linearity}}},
		{"offset",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayIntensities_offset}}},
		{"overload",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_overload}}},
		{"scaling",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayIntensities_scaling}}},
		{"undefined_value",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_undefined}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t array_structure_key[] = {
		{"id",cbf2nx_key_get_array_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t array_structure_map[] = {
		{"byte_order",CBF_MAP_NONE,NULL},
		{"compression_type",CBF_MAP_NONE,NULL},
		{"encoding_type",CBF_MAP_NONE,NULL},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t array_structure_list_key[] = {
		{"array_id",cbf2nx_key_get_array_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t array_structure_list_map[] = {
		{"axis_set_id",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayStructureList_axis_set_id}}},
		{"dimension",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayStructureList_dimension}}},
		{"direction",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayStructureList_direction}}},
		{"index",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayStructureList_index}}},
		{"precedence",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_ArrayStructureList_precedence}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_key[] = {
		{"id",cbf2nx_key_get_diffrn_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_map[] = {
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_data_frame_keys[] = {
		{"id",cbf2nx_key_get_frame_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_data_frame_map[] = {
		{"array_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_array}}},
		{"binary_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_binary}}},
		{"details",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"CBF_diffrn_data_frame__details",NULL,cbf_h5handle_require_detector,NULL,1}}}},
		{"detector_element_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_diffrn_detector_element}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_detector_keys[] = {
		{"id",cbf2nx_key_get_diffrnDetector_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_detector_map[] = {
		{"details",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"details",NULL,cbf_h5handle_require_detector,NULL,0}}}},
		{"detector",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"type",NULL,cbf_h5handle_require_detector,NULL,0}}}},
		{"diffrn_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_diffrn}}},
		{"dtime",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"dead_time","us",cbf_h5handle_require_detector,NULL,0}}}},
		{"gain_setting",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"gain_setting",NULL,cbf_h5handle_require_detector,NULL,0}}}},
		{"layer_thickness",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"sensor_thickness","mm",cbf_h5handle_require_detector,NULL,0}}}},
		{"number_of_axes",CBF_MAP_NONE,NULL},
		{"sensor_material",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"sensor_material",NULL,cbf_h5handle_require_detector,NULL,0}}}},
		{"threshold",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"threshold_energy","eV",cbf_h5handle_require_detector,NULL,0}}}},
		{"type",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"description",NULL,cbf_h5handle_require_detector,NULL,0}}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_detector_axis_keys[] = {
		{"detector_id",cbf2nx_key_get_diffrnDetector_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_detector_axis_map[] = {
		{"axis_id",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnDetectorAxis_axis}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_detector_element_keys[] = {
		{"id",cbf2nx_key_get_diffrnDetectorElement_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_detector_element_map[] = {
		{"center[1]",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"beam_center_x","mm",cbf_h5handle_require_detector,NULL,1}}}},
		{"center[2]",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"beam_center_y","mm",cbf_h5handle_require_detector,NULL,1}}}},
		{"detector_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_diffrn_detector}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_measurement_keys[] = {
		{"diffrn_id",cbf2nx_key_get_diffrn_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_measurement_map[] = {
		{"details",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"details",NULL,cbf_h5handle_require_goniometer,NULL,0}}}},
		{"device",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"local_name",NULL,cbf_h5handle_require_goniometer,NULL,0}}}},
		{"device_details",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"description",NULL,cbf_h5handle_require_goniometer,NULL,0}}}},
		{"device_type",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"type",NULL,cbf_h5handle_require_goniometer,NULL,0}}}},
		{"id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_diffrn_measurement}}},
		{"method",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"method",NULL,cbf_h5handle_require_entry,NULL,0}}}},
		{"number_of_axes",CBF_MAP_NONE,NULL},
		{"sample_detector_distance",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"distance","mm",cbf_h5handle_require_detector,NULL,1}}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_measurement_axis_keys[] = {
		{"measurement_id",cbf2nx_key_get_diffrnMeasurement_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_measurement_axis_map[] = {
		/* should also have 'measurement_device' somewhere, eventuallly */
		{"axis_id",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnMeasurementAxis_axis}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_radiation_keys[] = {
		{"diffrn_id",cbf2nx_key_get_diffrn_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_radiation_map[] = {
		{"collimation",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"collimation",NULL,cbf_h5handle_require_beam,NULL,0}}}},
		{"div_x_source",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"incident_divergence_x","degrees",cbf_h5handle_require_beam,NULL,0}}}},
		{"div_x_y_source",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"incident_divergence_xy","degrees^2",cbf_h5handle_require_beam,NULL,0}}}},
		{"div_y_source",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"incident_divergence_y","degrees",cbf_h5handle_require_beam,NULL,0}}}},
		{"inhomogeneity",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"beam_size_x","mm",cbf_h5handle_require_beam,(filter_func)(filter_inhomogeneity),0}}}},
		{"inhomogeneity",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"beam_size_y","mm",cbf_h5handle_require_beam,(filter_func)(filter_inhomogeneity),0}}}},
		{"monochromator",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"description",NULL,cbf_h5handle_require_monochromator,NULL,0}}}},
		{"polarizn_source_norm",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_PSN}}},
		{"polarizn_source_ratio",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_PSR}}},
        {"polarizn_source_norm_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_PSN_ESD}}},
        {"polarizn_source_ratio_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_PSR_ESD}}},
		{"probe",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_flstr,{"probe",NULL,cbf_h5handle_require_source,NULL,0}}}},
		{"polarizn_Stokes_I",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_I}}},
		{"polarizn_Stokes_Q",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_Q}}},
		{"polarizn_Stokes_U",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_U}}},
		{"polarizn_Stokes_V",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_V}}},
		{"polarizn_Stokes_I_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_I_ESD}}},
		{"polarizn_Stokes_Q_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_Q_ESD}}},
		{"polarizn_Stokes_U_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_U_ESD}}},
		{"polarizn_Stokes_V_esd",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnRadiation_V_ESD}}},
		{"wavelength_id",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_wavelength_id}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_radiation_wavelength_keys[] = {
		{"id",cbf2nx_key_get_wavelength_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_radiation_wavelength_map[] = {
		{"wavelength",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"incident_wavelength","angstroms",cbf_h5handle_require_beam,NULL,1}}}},
		{"wt",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"weight",NULL,cbf_h5handle_require_beam,NULL,1}}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_refln_key[] = {
		{"frame_id",cbf2nx_key_get_frame_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_refln_map[] = {
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_scan_keys[] = {
		{"id",cbf2nx_key_get_scan_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_scan_map[] = {
		{"date_start",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"start_time",NULL,cbf_h5handle_require_entry,NULL,0}}}},
		{"date_end",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"end_time",NULL,cbf_h5handle_require_entry,NULL,0}}}},
		{"frame_id_start",CBF_MAP_NONE,NULL},
		{"frame_id_end",CBF_MAP_NONE,NULL},
		{"frames",CBF_MAP_NONE,NULL},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_scan_axis_keys[] = {
		{"scan_id",cbf2nx_key_get_scan_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_scan_axis_map[] = {
		{"angle_increment",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_angleIncr}}},
		{"angle_rstrt_incr",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_angleRstrtIncr}}},
		{"angle_start",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_angleStrt}}},
		{"axis_id",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_axis}}},
		{"displacement_increment",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_dispIncr}}},
		{"displacement_rstrt_incr",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_dispRstrtIncr}}},
		{"displacement_start",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanAxis_dispStrt}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_scan_frame_keys[] = {
		{"scan_id",cbf2nx_key_get_scan_id,strcmp},
		{"frame_id",cbf2nx_key_get_frame_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_scan_frame_map[] = {
		{"date",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"frame_start_time",NULL,cbf_h5handle_require_detector,NULL,1}}}},
		{"frame_number",CBF_MAP_KEY,(cbf2nx_set_key_t[]){{cbf2nx_key_set_frame_number}}},
		{"time_period",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"frame_time","s",cbf_h5handle_require_detector,NULL,1}}}},
        /* deprecated erroneous use of integration period will be supported for read with a warning */
        {"integration_period",CBF_MAP_DATA_DEPRECATED,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"frame_time","s",cbf_h5handle_require_detector,NULL,1}}}},
		{"integration_time",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"count_time","s",cbf_h5handle_require_detector,NULL,1}}}},
        /* deprecated erroneous use of exposure will be supported for read with a warning */
        {"exposure_time",CBF_MAP_DATA_DEPRECATED,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"count_time","s",cbf_h5handle_require_detector,NULL,1}}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_scan_frame_axis_keys[] = {
		{"frame_id",cbf2nx_key_get_frame_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_scan_frame_axis_map[] = {
		{"angle",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanFrameAxis_angle}}},
		{"axis_id",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanFrameAxis_axis}}},
		{"displacement",CBF_MAP_CACHE,(cbf2nx_cache_item_t[]){{cache_DiffrnScanFrameAxis_disp}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf_primary_key_t diffrn_source_keys[] = {
		{"diffrn_id",cbf2nx_key_get_diffrn_id,strcmp},
		{NULL,NULL,NULL},
	};

	static cbf2nx_column_map_t diffrn_source_map[] = {
		{"current",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"current","mA",cbf_h5handle_require_source,NULL,0}}}},
		{"power",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"power","kW",cbf_h5handle_require_source,NULL,0}}}},
		{"source",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"type",NULL,cbf_h5handle_require_source,NULL,0}}}},
		{"target",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"target_material",NULL,cbf_h5handle_require_source,NULL,0}}}},
		{"type",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_vlstr,{"name",NULL,cbf_h5handle_require_source,NULL,0}}}},
		{"voltage",CBF_MAP_DATA,(cbf2nx_convert_t[]){{cbf_convert_cbf2nx_double,{"voltage","kV",cbf_h5handle_require_source,NULL,0}}}},
		{NULL,CBF_MAP_NONE,NULL},
	};

	static cbf2nx_category_map_t cbf_map[] = {
	{
			"array_data",
			array_data_key,
			array_data_map,
			{sizeof(ArrayDataCache), ctor_ArrayDataCache, NULL},
			process_ArrayDataCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"array_intensities",
			array_intensities_key,
			array_intensities_map,
			{sizeof(ArrayIntensitiesCache), ctor_ArrayIntensitiesCache, NULL},
			process_ArrayIntensitiesCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"array_structure",
			array_structure_key,
			array_structure_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"array_structure_list",
			array_structure_list_key,
			array_structure_list_map,
			{sizeof(ArrayStructureListCache), ctor_ArrayStructureListCache, NULL},
			process_ArrayStructureListCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn",
			diffrn_key,
			diffrn_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_data_frame",
			diffrn_data_frame_keys,
			diffrn_data_frame_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_detector",
			diffrn_detector_keys,
			diffrn_detector_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_detector_axis",
			diffrn_detector_axis_keys,
			diffrn_detector_axis_map,
			{sizeof(DiffrnDetectorAxisRCache), ctor_DiffrnDetectorAxisRCache, NULL},
			process_DiffrnDetectorAxisRCache,
			{sizeof(DiffrnDetectorAxisTCache), ctor_DiffrnDetectorAxisTCache, dtor_DiffrnDetectorAxisTCache},
			process_DiffrnDetectorAxisTCache,
		},
		{
			"diffrn_detector_element",
			diffrn_detector_element_keys,
			diffrn_detector_element_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_measurement",
			diffrn_measurement_keys,
			diffrn_measurement_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_measurement_axis",
			diffrn_measurement_axis_keys,
			diffrn_measurement_axis_map,
			{sizeof(DiffrnMeasurementAxisRCache), ctor_DiffrnMeasurementAxisRCache, NULL},
			process_DiffrnMeasurementAxisRCache,
			{sizeof(DiffrnMeasurementAxisTCache), ctor_DiffrnMeasurementAxisTCache, dtor_DiffrnMeasurementAxisTCache},
			process_DiffrnMeasurementAxisTCache,
		},
		{
			"diffrn_radiation",
			diffrn_radiation_keys,
			diffrn_radiation_map,
			{sizeof(DiffrnRadiationRowCache), ctor_DiffrnRadiationRowCache, NULL},
			process_DiffrnRadiationRowCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_radiation_wavelength",
			diffrn_radiation_wavelength_keys,
			diffrn_radiation_wavelength_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_refln",
			diffrn_refln_key,
			diffrn_refln_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_scan",
			diffrn_scan_keys,
			diffrn_scan_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_scan_axis",
			diffrn_scan_axis_keys,
			diffrn_scan_axis_map,
			{sizeof(DiffrnScanAxisCache), ctor_DiffrnScanAxisCache, NULL},
			process_DiffrnScanAxisCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_scan_frame",
			diffrn_scan_frame_keys,
			diffrn_scan_frame_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_scan_frame_axis",
			diffrn_scan_frame_axis_keys,
			diffrn_scan_frame_axis_map,
			{sizeof(DiffrnScanFrameAxisCache), ctor_DiffrnScanFrameAxisCache, NULL},
			process_DiffrnScanFrameAxisCache,
			{0, NULL, NULL}, NULL,
		},
		{
			"diffrn_source",
			diffrn_source_keys,
			diffrn_source_map,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
		{
			NULL, NULL, NULL,
			{0, NULL, NULL}, NULL,
			{0, NULL, NULL}, NULL,
		},
	};

            /*
	Search a list of category mappings for one with a given name, returning the mapping data if found or NULL otherwise.
             */
	static const cbf2nx_category_map_t * cbf2nx_find_category_mapping
			(const cbf2nx_category_map_t * catmap, /*< the list of category mappings to search within */
			 const char * const name /*< the name of the category mapping to search for */)
                {
		if (!catmap || !name) {
			return NULL;
		} else {
			for (; catmap->name; ++catmap) {
				if (!strcmp(catmap->name,name)) {
					return catmap;
                        }
                    }
			return NULL;
                        }
                    }

                    /*
	Write some data to a hdf5 handle according to the conversion method(s) specified in the given mapping.

	Searches the given column mapping array for the method to map the given column, extracts the relevant
	information from the mapping data and applies it, which usually involves forwarding to a function with
	a signature which depends on the type of conversion to be performed.

	This iterates over all columns in the mapping to allow multiple conversions to be applied for a single
	column.
                     */
	static int cbf2nx_apply_conversions
                    (cbf_h5handle h5handle,
                     cbf_cbf2nx_key_t * const key,
                     const cbf2nx_column_map_t * const colmap_begin,
                     cbf_node * const column,
                     const unsigned int row,
                     void * const row_cache,
                     const int list,
                     const unsigned int matched)
	{
		int error = CBF_SUCCESS;
		if (!key || !column) {
			error |= CBF_ARGUMENT;
                        } else {
			int in_list = 0;
			const unsigned int indent = 1+key->indent;
			if (colmap_begin) {
				const cbf2nx_column_map_t * colmap;
				for (colmap = colmap_begin; CBF_SUCCESS==error && colmap->name; ++colmap) {
                    if (!cbf_cistrcmp(colmap->name,column->name)) {
                        int state = 3;
						in_list = 1;
						switch (colmap->type) {
							case CBF_MAP_NONE: {
								state = 2;
								break;
                        }
                            case CBF_MAP_DATA_DEPRECATED: {
                                if (h5handle->logfile && !matched) {
                                  fprintf(h5handle->logfile,"Deprecated CBF tag '%s' \n", column->name);
                                }
                                }
							case CBF_MAP_DATA: {
								const cbf2nx_convert_t * const conversion = (const cbf2nx_convert_t *)(colmap->data);
								state = 1;
								if (!conversion) {
									cbf_debug_print("error: malformed mapping method");
									error |= CBF_FORMAT;
                        } else {
									CBF_CALL(conversion->convert(column,row,h5handle,&conversion->data));
                        }
								break;
							}
							case CBF_MAP_KEY: {
								const cbf2nx_set_key_t * const set_key = (const cbf2nx_set_key_t *)(colmap->data);
								state = 1;
								if (!set_key) {
									cbf_debug_print("error: malformed mapping method");
									error |= CBF_FORMAT;
                        } else {
									const char * val = NULL;
									CBF_CALL(cbf_node_get_value(column, row, &val));
									CBF_CALL(set_key->set_key(key,val));
                        }
								break;
							}
							case CBF_MAP_CACHE: {
								const cbf2nx_cache_item_t * const cache_item = (const cbf2nx_cache_item_t *)(colmap->data);
								state = 1;
								if (!cache_item) {
									cbf_debug_print("error: malformed mapping method");
									error |= CBF_FORMAT;
                    } else {
									CBF_CALL(cache_item->cache_item(column,row,row_cache));
                    }
								break;
                }
							default: {
								state = 1;
								cbf_debug_print("error: invalid mapping method");
                            error |= CBF_FORMAT;
				}
				}
						if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,state);
			}
		}
            }
            if (!in_list && h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,0);
        }
		return error;
	}

    /*
	Define a type to hold data for a single row of the 'axis' category.
	The validity of string types can be tested by comparison to 'NULL',
	the validity of vector types can be tested by checking if the number
	of elements found (in 'nComponent') is 3.
	 */
	typedef struct cbf_axis_data_t
	{
		const char * id;
		const char * depends_on;
		const char * equipment;
        const char * equipment_component;
        const char * rotation_axis;
        double rotation;
		const char * type;
		double offset[3];
		double vector[3];
		unsigned int nOffset;
		unsigned int nVector;
        int flags;
	} cbf_axis_data_t;

	/*
	Generate a set of reasonable initial values for 'cbf_axis_data_t',
	used to initialise and reset objects of that type.
	*/
	static cbf_axis_data_t cbf_axis_data_init()
				{
        return (cbf_axis_data_t) {NULL,NULL,NULL,NULL,NULL,0.,NULL,{0.,0.,0.},{0.,0.,0.},0,0,0};
				}

    /*
	Read a given row of data from the given axis category, after initialising
	the 'data' struct to sensible default values. Unrecognised columns will
	cause a warning to be printed, but are otherwise ignored rather than causing
	an error. Missing columns are not logged.

	\return An error code.
	*/
	static int cbf_read_axis_row
			(cbf_axis_data_t * const data /*< The location where extracted data should be stored. */,
			 cbf_node * const category /*< The category to extract data from. */,
			 const unsigned int row /*< The row to extract data from. */)
	{
        int error = CBF_SUCCESS;
		/* check that the arguments are sensible */
		if (!data || !category) {
            error |= CBF_ARGUMENT;
        } else {
			cbf_node * const * column_it;
			/* initialise the 'axis_data' type to reasonable defaults */
			*data = cbf_axis_data_init();
			/* iterate through all columns, storing values in the 'axis_data' type for later use */
			for (column_it = category->child; !error && column_it != category->children+category->child; ++column_it) {
				cbf_node * const column = *column_it;
				if (!strcmp(column->name,"id")) {
					CBF_CALL(cbf_node_get_value(column, row, &data->id));
				} else if (!strcmp(column->name,"depends_on")) {
					CBF_CALL(cbf_node_get_value(column, row, &data->depends_on));
				} else if (!strcmp(column->name,"equipment")) {
					CBF_CALL(cbf_node_get_value(column, row, &data->equipment));
                } else if (!strcmp(column->name,"equipment_component")) {
                    CBF_CALL(cbf_node_get_value(column, row, &data->equipment_component));
                } else if (!strcmp(column->name,"rotation_axis")) {
                    CBF_CALL(cbf_node_get_value(column, row, &data->rotation_axis));
                } else if (!strcmp(column->name,"rotation")) {
                    CBF_CALL(cbf_node_get_doublevalue(column, row, &data->rotation));
				} else if (!strcmp(column->name,"type")) {
					CBF_CALL(cbf_node_get_value(column, row, &data->type));
				} else if (!strcmp(column->name,"offset[1]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 0+data->offset));
					if (!error) ++data->nOffset;
				} else if (!strcmp(column->name,"offset[2]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 1+data->offset));
					if (!error) ++data->nOffset;
				} else if (!strcmp(column->name,"offset[3]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 2+data->offset));
					if (!error) ++data->nOffset;
				} else if (!strcmp(column->name,"vector[1]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 0+data->vector));
					if (!error) ++data->nVector;
				} else if (!strcmp(column->name,"vector[2]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 1+data->vector));
					if (!error) ++data->nVector;
				} else if (!strcmp(column->name,"vector[3]")) {
					CBF_CALL(cbf_node_get_doublevalue(column, row, 2+data->vector));
					if (!error) ++data->nVector;
			} else {
					cbf_debug_print2("warning: unrecognised column in 'axis' table:\n %s\n",column->name);
				}
			}
		}
		return error;
	}

	/*
	This function iterates through stored axis sets, it doesn't iterate of a subset of rows within a table,
	so it shouldn't be forced into the same processing model as the conversion functions which do.

	See the comments for a description of what this function does.
	*/
    static int cbf_write_cbf2nx__array_structure_list_axis
                    (cbf_handle handle,
                     cbf_h5handle h5handle,
                     cbf_cbf2nx_key_t * const key,
                     const int list)
	{
		int error = CBF_SUCCESS;
        unsigned int matched = 0;
        const char categoryName[] = "array_structure_list_axis";
#ifdef CBF_USE_ULP
        cmp_double_param_t cmp_double_params;
        void * cmp_params = &cmp_double_params;

		/* set up the comparison parameters */
        cmp_double_params.cmp_double_as_float = cbf_has_ULP64() ? h5handle->cmp_double_as_float : 1;
        cmp_double_params.ulp32 = h5handle->float_ulp;
#ifndef NO_UINT64_TYPE
        cmp_double_params.ulp64 = h5handle->double_ulp;
#endif
#else
        void * cmp_params = 0;
        CBF_UNUSED(cmp_params);
#endif

		/* check arguments */
		if (!handle) {
            cbf_debug_print("Invalid handle given\n");
            error |= CBF_ARGUMENT;
        } else if (!h5handle) {
            cbf_debug_print("Invalid hdf5 handle given\n");
            error |= CBF_ARGUMENT;
		} else if
			(!key ||
			!key->arrayAxisSet.axis_set_id ||
			!key->arrayAxisSet.direction ||
			!key->arrayAxisSet.precedence ||
			0==key->arrayAxisSet.count)
		{
            cbf_debug_print("Bad key given\n");
            error |= CBF_ARGUMENT;
        } else if (CBF_SUCCESS!=(error|=cbf_find_category(handle,categoryName))) {
            cbf_debug_print3("error: couldn't find category '%s': %s\n",categoryName,cbf_strerror(error));
        } else {
            cbf_node * const category = handle->node;
            cbf_node * primary_keys[1];
            const unsigned int npk = sizeof(primary_keys)/sizeof(*primary_keys);
            unsigned int indent = 1+key->indent;
            unsigned int * axes = NULL;
            unsigned int nRows;
            unsigned int set;
            if (h5handle->logfile) _cbf_write_name(h5handle->logfile,categoryName,0,key->indent,1);
            if (key->categories) {
                cbf_node * * it;
                cbf_node * const * const end = key->nCat+key->categories;
                for (it = key->categories; end != it; ++it) {
                    if (*it) {
                        *it = strcmp((*it)->name,categoryName) ? *it : NULL;
		}
		}
		}
            /* check that I have some children, and try to find the primary key columns */
            if (0==category->children) {
                cbf_debug_print2("error: %s\n","category has no children");
                error |= CBF_NOTFOUND;
            } else {
                nRows = category->child[0]->children;
                axes = malloc(sizeof(unsigned int)*nRows);
                CBF_CALL(cbf_find_child(primary_keys+0, category, "axis_set_id"));
            }
            /*
             - iterate over axis sets
             - count the number of axes in each set, caching them for later reference
             - use the number of axes (and possibly other data) to test for valid data
             */
            for (set = 0; CBF_SUCCESS==error && set != key->arrayAxisSet.count; ++set) {
                unsigned int nAxes = 0;
                unsigned int row;
                for (row = 0; row != nRows; ++row) {
                    const char * set_id = NULL;
                    if (CBF_SUCCESS!=(error|=cbf_node_get_value(primary_keys[0], row, &set_id))) {
                        cbf_debug_print2("error: %s\n",cbf_strerror(error));
                    } else if (!strcmp(key->arrayAxisSet.axis_set_id[set],set_id)) {
                        axes[nAxes++] = row;
                    }
                }
                /*
                 I know how many (and which) entries in ASLA relate to the current axis set:
                 - check the number of axes in the set
                 - extract and convert data as appropriate
                 */
                if (0 == nAxes) {
                    /* no axes - missing data? */
                    cbf_debug_print2("error: no axes found for set '%s'\n",key->arrayAxisSet.axis_set_id[set]);
                    error |= CBF_NOTFOUND;
                } else if (1 == nAxes) {
                    /* 1 axis - most common case */
                    cbf_node * const * column_it;
                    double angle = 0., angle_incr = 0.;
                    int have_angle = 0, have_angle_incr = 0;
                    double disp = 0., disp_incr = 0.;
                    int have_disp = 0, have_disp_incr = 0;
                    double angular_pitch = 0., radial_pitch = 0.;
                    int have_angular_pitch = 0, have_radial_pitch = 0;
						const char * axis = NULL;
                    for (column_it = category->child; CBF_SUCCESS==error && column_it != category->children+category->child; ++column_it) {
                        cbf_node * const column = *column_it;
                        int pk = 0;
                        cbf_node * const * it;
                        cbf_node * const * const end = npk+primary_keys;
                        for (it = primary_keys; end != it; ++it) {
                            pk = column==*it ? 1 : pk;
                        }
                        /*
						I now have all the information required to read some relevant data:
                         - if a column is used as a primary key, ignore it but record it as processed
                         - if a column has a recognised name, perform the conversion
                         - otherwise, record the column as not processed and carry on
                         */
                        if (pk) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
                        } else if (!cbf_cistrcmp(column->name,"angle")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &angle));
								if (!error) have_angle = 1;
                        } else if (!cbf_cistrcmp(column->name,"angle_increment")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &angle_incr));
								if (!error) have_angle_incr = 1;
                        } else if (!cbf_cistrcmp(column->name,"angular_pitch")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &angular_pitch));
								if (!error) have_angular_pitch = 1;
                        } else if (!cbf_cistrcmp(column->name,"axis_id")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
                            CBF_CALL(cbf_node_get_value(column, axes[0], &axis));
                        } else if (!cbf_cistrcmp(column->name,"displacement")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &disp));
								if (!error) have_disp = 1;
                        } else if (!cbf_cistrcmp(column->name,"displacement_increment")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &disp_incr));
								if (!error) have_disp_incr = 1;
                        } else if (!cbf_cistrcmp(column->name,"radial_pitch")) {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,1);
								CBF_CALL(cbf_node_get_doublevalue(column, axes[0], &radial_pitch));
								if (!error) have_radial_pitch = 1;
                            } else {
                            if (h5handle->logfile && !matched) _cbf_write_name(h5handle->logfile,column->name,0,indent,0);
                        }
                    }
                    ++matched;
						if (CBF_SUCCESS == error) {
                        /*
                         I now have the data for the current row, use it to write the corresponding items to HDF5.
                         The exact comparison is correct; a difference of just 1 ulp from 0.0 implies that I need
                         to treat the setting as non-zero, because 0.0 is used as a signalling value instead of a
                         computed value. Compilers will complain about this: ignore them, they are wrong.
                         */
						if
							(have_disp && have_disp_incr &&
                            (!have_angle || 0.==angle) && (!have_angle_incr || 0.==angle_incr) &&
                            (!have_angular_pitch || 0.==angular_pitch) && (!have_radial_pitch || 0.==radial_pitch))
                        { /* it looks like a 1 dimensional displacement */
							cbf_axis_data_t axis_settings = cbf_axis_data_init();
                            { /* write the pixel sizes to NXdetector */
                                hid_t detector = CBF_H5FAIL;
							    hid_t dset = CBF_H5FAIL;
                                const char empty[] = "";
                                const char pixel_x[] = "x_pixel_size";
                                const char pixel_y[] = "y_pixel_size";
                                const char * p[] = {empty, pixel_y, pixel_x};
                                CBF_CALL(cbf_h5handle_require_detector(h5handle,&detector,0));
                                CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector,&dset,p[key->arrayAxisSet.precedence[set]],fabs(disp_incr),cmp_double,cmp_params));
                                CBF_CALL(cbf_H5Arequire_string(dset,"units","mm"));
                                cbf_H5Dfree(dset);
                            }
							/* select the axis and extract the data it contains */
                            if (CBF_SUCCESS!=(error|=cbf_find_category(handle,"axis"))) {
                                cbf_debug_print2("error: %s\n",cbf_strerror(error));
                            } else {
                                cbf_node * const axisCategory = handle->node;
                                if (CBF_SUCCESS!=(error|=cbf_find_column(handle,"id"))) {
                                    cbf_debug_print2("error: %s\n",cbf_strerror(error));
                                } else if (CBF_SUCCESS!=(error|=cbf_find_row(handle,axis))) {
                                    cbf_debug_print2("error: problem finding '%s' in axis category\n",axis);
                                    cbf_debug_print(cbf_strerror(error));
                                } else {
									CBF_CALL(cbf_read_axis_row(&axis_settings,axisCategory,handle->row));
                                            }
                                            }
							/* calculate the array of values the axis should have, and store the axis */
                            if (CBF_SUCCESS==error) {
                                double * const axisData = malloc(sizeof(double)*key->arrayAxisSet.dimension[set]);
                                if (!axisData) {
                                    cbf_debug_print2("error: %s\n",cbf_strerror(CBF_ALLOC));
                                    error |= CBF_ALLOC;
                                } else {
                                    unsigned int i;
                                    const unsigned int dimension = key->arrayAxisSet.dimension[set];
									const char * depends_on_path = NULL;
                                    const char * rotation_axis_path = NULL;
                                    hid_t dset = CBF_H5FAIL;
							const hsize_t dim[] = {dimension};
							const hsize_t max[] = {H5S_UNLIMITED};
							const hsize_t count[] = {dim[0]};
                                    const hsize_t offset[] = {0};
							hsize_t buf[] = {0};
                                    const int found = cbf_H5Dfind2(h5handle->hfile,&dset,key->arrayAxisSet.path[set],1,0,buf,H5T_IEEE_F64LE);
                                    /* initialise the axisData array */
                                    if (!key->arrayAxisSet.direction || !key->arrayAxisSet.direction[set]) {
                                        cbf_debug_print2("error: %s\n",cbf_strerror(CBF_UNDEFINED));
                                        error |= CBF_UNDEFINED;
                                    } else if (!strcmp(key->arrayAxisSet.direction[set],"increasing")) {
                                        for (i = 0; i < dimension; ++i) axisData[i] = disp+i*disp_incr;
                                    } else if (!strcmp(key->arrayAxisSet.direction[set],"decreasing")) {
                                        for (i = 0; i < dimension; ++i) axisData[i] = disp+(dimension-i-1)*disp_incr;
                                    } else {
                                        cbf_debug_print2("error: %s\n",cbf_strerror(CBF_FORMAT));
                                        error |= CBF_FORMAT;
                                    }
                                    /* ensure a suitable dataset exists, or create one */
							if (CBF_SUCCESS==error) {
								if (CBF_SUCCESS == found) {
                                            /* TODO: check dataset dimensions */
									double * const currData = malloc(sizeof(double)*dimension);
                                            if (!currData) {
                                                cbf_debug_print2("error: %s\n",cbf_strerror(CBF_ALLOC));
                                                error |= CBF_ALLOC;
                                            }
                                            CBF_CALL(cbf_H5Dread2(dset,offset,0,count,currData,H5T_NATIVE_DOUBLE));
                                            if (CBF_SUCCESS==error) {
                                                if (CBFM_cmp_double(axisData, currData, dimension, cmp_params)) {
                                                    cbf_debug_print("error: image axis data doesn't match");
										error |= CBF_H5DIFFERENT;
									}
                                            }
									free((void*)currData);
								} else if (CBF_NOTFOUND == found) {
                                            CBF_CALL(cbf_H5Dcreate(h5handle->hfile,&dset,key->arrayAxisSet.path[set],1,dim,max,count,H5T_IEEE_F64LE));
                                            CBF_CALL(cbf_H5Dwrite2(dset,offset,0,count,axisData,H5T_NATIVE_DOUBLE));
								} else {
                                            cbf_debug_print2("error: %s\n",cbf_strerror(found));
									error |= found;
								}
                                    }
                                    /*
                                     Get dependency for current axis set:
                                     - In the general case there may be multiple axes in the set, each with a dependency.
                                     - I need to find the real dependencies in this function, because I should only know
                                     enough about the axes in the set to be able to do that here.
                                     - A dependency is always on an axis, but might imply dependency on a different set.
                                     - Iff the parent axis is in a set then the dependency is on that set.
                                     - As the dependency may be on an axis, all axes must already be processed.
                                     - As the dependency may be on a set, all sets must have been assigned a path.
                                     - Neglect possible complications caused by one axis being in multiple sets.
                                     */
                                    if (CBF_SUCCESS==error) {
                                        cbf_node * axis_id = NULL;
                                        if (CBF_SUCCESS!=(error|=cbf_find_child(&axis_id, category, "axis_id"))) {
                                            cbf_debug_print2("error: %s\n",cbf_strerror(error));
                                        } else {
                                            const char * id = NULL;
                                            unsigned int i;
                                            /* search for the parent axis in ASLA.axis_id: */
                                            for (i = 0; i != axis_id->children; ++i) {
                                                if (CBF_SUCCESS!=(error|=cbf_node_get_value(axis_id, i, &id))) {
                                                    cbf_debug_print2("error: %s\n",cbf_strerror(error));
                                                } else {
													if (!strcmp(id,axis_settings.depends_on)) break;
                                                }
                                            }
                                            if (i != axis_id->children) {
                                                /* the parent axis exists within an axis set - the dependency is the path for that set */
                                                if (CBF_SUCCESS!=(error|=cbf_node_get_value(primary_keys[0], i, &id))) {
                                                    cbf_debug_print2("error: %s\n",cbf_strerror(error));
                                                } else {
                                                    for (i = 0; i != key->arrayAxisSet.count; ++i) {
                                                        if (!strcmp(key->arrayAxisSet.axis_set_id[i],id)) break;
                                                    }
                                                    if (i == key->arrayAxisSet.count) {
                                                        cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTFOUND));
                                                        error |= CBF_NOTFOUND;
                                                    } else {
														depends_on_path = key->arrayAxisSet.path[i];
                                                    }
                                                }
                                            } else {
                                                /* the parent axis is a free axis - the dependency is the path for that axis */
                                                for (i = 0; i != key->axis.count; ++i) {
													if (!strcmp(key->axis.axis_id[i],axis_settings.depends_on)) break;
                                                }
                                                if (i == key->axis.count) {
                                                    cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTFOUND));
                                                    error |= CBF_NOTFOUND;
                                                } else {
                                                    depends_on_path = key->axis.path[i];
                                                }
                                            }
                                        }
                                    }
                                    /* add/check attributes using the data extracted from the axis */
                                    if (CBF_SUCCESS==error) {
                                        CBF_CALL(cbf_H5Arequire_string(dset,"transformation_type","translation"));
                                        CBF_CALL(cbf_H5Arequire_string(dset,"units","mm"));
                                    }
                                    if (CBF_SUCCESS==error && depends_on_path) {
                                        CBF_CALL(cbf_H5Arequire_string(dset,"depends_on",depends_on_path));
                                    }
                                    if (CBF_SUCCESS==error && axis_settings.equipment) {
                                        CBF_CALL(cbf_H5Arequire_string(dset,"equipment",axis_settings.equipment));
                                    }
                                    if (CBF_SUCCESS==error && axis_settings.equipment_component && strlen(axis_settings.equipment_component)>0) {
                                        CBF_CALL(cbf_H5Arequire_string(dset,"equipment_component",axis_settings.equipment_component));
                                    }
                                    if (CBF_SUCCESS==error && axis_settings.rotation_axis && strlen(axis_settings.rotation_axis)>0) {
                                        /* *** Change to a path instead of an axis name *** */
                                        CBF_CALL(cbf_H5Arequire_string(dset,"rotation_axis",axis_settings.rotation_axis));
                                        {
                                            const hsize_t rdim[] = {1};
                                            hsize_t rbuf[] = {0};
                                            CBF_CALL(CBFM_H5Arequire_cmp2(dset,"rotation",1,rdim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,&(axis_settings.rotation),rbuf,cmp_double,cmp_params));
                                        }
                                        
                                    }
									if (CBF_SUCCESS==error && axis_settings.nOffset==3) {
										double offset[3];
                                        const hsize_t vdim[] = {3};
                                        hsize_t vbuf[] = {0};
                                        CBF_CALL(cbf_apply_matrix(key->matrix,axis_settings.offset,offset));
                                        CBF_CALL(CBFM_H5Arequire_cmp2(dset,"offset",1,vdim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,offset,vbuf,cmp_double,cmp_params));
                                        CBF_CALL(cbf_H5Arequire_string(dset,"offset_units","mm"));
                                    }
									if (CBF_SUCCESS==error && axis_settings.nVector==3) {
										double vector[3];
                                        const hsize_t vdim[] = {3};
                                        hsize_t vbuf[] = {0};
                                        CBF_CALL(cbf_apply_matrix(key->matrix,axis_settings.vector,vector));
                                        CBF_CALL(CBFM_H5Arequire_cmp2(dset,"vector",1,vdim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,vector,vbuf,cmp_double,cmp_params));
                                    }
								cbf_H5Dfree(dset);
							}
                                free((void*)axisData);
						}
                        } else {
                            cbf_debug_print("error: unrecognised combination of settings");
                            error |= CBF_FORMAT;
					}
				}
                } else {
                    /* unhandled number of axes - error */
                    cbf_debug_print("error: unsupported array structure");
                    error |= CBF_NOTIMPLEMENTED;
			}
		}
            if (!matched) {
                /* TODO: in some cases this will be an error, find them */
                cbf_debug_print("warning: No data located");
	}
            free((void*)axes);
		}
        return error;
	}

            /*
     Special function to support axis conversions back from NeXus to
     CBF by recording the axes CBF_X_, CBF_Y_, CBF_Z_, BEAM, GRAVITY,
     UP and other general axes in NXentry/NXinstrument/NXtranformations,
     if possible.

     */
    static int cbf_write_cbf2nx__cbf_general_axes
    (cbf_handle handle,
     cbf_h5handle h5handle,
     double matrix[3][3])
    {
        
        const char* anames[7] = {"CBF_X_","CBF_Y_","CBF_Z_","BEAM", "SOURCE", "GRAVITY", "UP"};
        int afound[7] = {0,0,0,0,0,0,0};
        double beamvector[3] = {0.,0.,-1.};
        double sourcevector[3] = {0.,0.,1.};
        double gravityvector[3]= {0.,-1.,0.};
        double upvector[3]= {0.,1.,0.};
        hid_t instrument = CBF_H5FAIL;
        hid_t poise = CBF_H5FAIL;
        int error;
        unsigned int rows, row;
        hid_t dset = CBF_H5FAIL;
        const hsize_t max[] = {1};
        const hsize_t cnk[] = {1};
        hsize_t buf[] = {0};
        
        
        if (!handle || !h5handle || !matrix) return CBF_ARGUMENT;
        
        error = 0;
        
        /* ensure the handle contains some basic structure */
        CBF_CALL(cbf_h5handle_require_entry(h5handle,0,0));
        CBF_CALL(cbf_h5handle_require_instrument(h5handle,&instrument,0));
        CBF_CALL(cbf_H5Grequire(instrument,&poise,"transformations"));
        CBF_CALL(cbf_H5Arequire_string(poise,"NXclass","NXtransformations"));
        
        CBF_CALL(cbf_find_category(handle, "axis"));
        CBF_CALL(cbf_find_column(handle,"id"));
        CBF_CALL(cbf_count_rows(handle,&rows));
        
        for(row=0; row < rows+7 && !error; row++) {
            const char * axis_id;
            const char * equipment;
            const char * equipment_component;
            const char * depends_on;
            const char * rotation_axis;
            const char * type;
            const char * system;
            double rotation;
            double vector[3], offset[3];
            double cbfvector[3], cbfoffset[3];
            
            if (row < rows) {
                
                CBF_CALL(cbf_find_category(handle, "axis"));
                CBF_CALL(cbf_find_column(handle,"id"));
                CBF_CALL(cbf_select_row(handle,row));
                CBF_CALL(cbf_find_column(handle,"id"));
                CBF_CALL(cbf_get_value(handle,&axis_id));
                
                equipment = "general";
                if (!cbf_find_column(handle,"equipment")) {
                    CBF_CALL(cbf_get_value(handle,&equipment));
                    if (!equipment)  equipment = "general";
                }
                
                cbf_debug_print3("processing axis %s for equipment %s\n",axis_id,equipment);
                
                if (!cbf_cistrcmp(equipment,"detector")||
                    !cbf_cistrcmp(equipment,"goniometer")) continue;
                
                equipment = "general";
                
                depends_on = ".";
                if (!cbf_find_column(handle,"depends_on")) {
                    CBF_CALL(cbf_get_value(handle,&depends_on));
                    if (!depends_on) depends_on = ".";
                }
                
                rotation_axis= ".";
                if (!cbf_find_column(handle,"rotation_axis")) {
                    CBF_CALL(cbf_get_value(handle,&depends_on));
                    if (!rotation_axis) rotation_axis = ".";
                }
                
                rotation = 0.;
                if (!cbf_find_column(handle,"rotation")) {
                    CBF_CALL(cbf_get_doublevalue(handle,&rotation));
                }
                
                type = "general";
                if (!cbf_find_column(handle,"type")) {
                    CBF_CALL(cbf_get_value(handle,&type));
                    if (!type) type = "general";
                }
                
                system = "laboratory";
                if (!cbf_find_column(handle,"system")) {
                    CBF_CALL(cbf_get_value(handle,&system));
                    if (!system||!system[0]) system = "laboratory";
                    if (cbf_cistrcmp(system,".")||cbf_cistrcmp(system,"?"))
                        system = "laboratory";
                }
                
                if (cbf_cistrcmp(system,"laboratory")) {
                    CBF_CALL(cbf_get_axis_vector_and_offset(handle,axis_id,
                                                            vector, offset));
                    cbfvector[0] = vector[0];
                    cbfvector[1] = vector[1];
                    cbfvector[2] = vector[2];
                } else {
                    CBF_CALL(cbf_get_axis_poise(handle, 0.,
                                                (double *)cbfvector,(double *)cbfvector+1,(double *)cbfvector+2,
                                                (double *)cbfoffset,(double *)cbfoffset+1,(double *)cbfoffset+2,
                                                NULL,axis_id,NULL));
                    system = "McStas_absolute";
                    CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                    CBF_CALL(cbf_apply_matrix(matrix,cbfoffset,offset));
                }
                
                if (!cbf_cistrcmp(axis_id,"BEAM")) {
                    if (CBF_SUCCESS== error) {
                        afound[3] = 1;
                        beamvector[0] = cbfvector[0];
                        beamvector[1] = cbfvector[1];
                        beamvector[2] = cbfvector[2];
                        sourcevector[0] = -beamvector[0];
                        sourcevector[1] = -beamvector[1];
                        sourcevector[2] = -beamvector[2];
                    }
                }
                if (!cbf_cistrcmp(axis_id,"SOURCE")) {
                    if (CBF_SUCCESS== error) {
                        afound[4] = 1;
                        sourcevector[0] = cbfvector[0];
                        sourcevector[1] = cbfvector[1];
                        sourcevector[2] = cbfvector[2];
                        beamvector[0] = -sourcevector[0];
                        beamvector[1] = -sourcevector[1];
                        beamvector[2] = -sourcevector[2];
                    }
                }
                if (!cbf_cistrcmp(axis_id,"GRAVITY")) {
                    if (CBF_SUCCESS== error) {
                        afound[5] = 1;
                        gravityvector[0] = cbfvector[0];
                        gravityvector[1] = cbfvector[1];
                        gravityvector[2] = cbfvector[2];
                        upvector[0] = -gravityvector[0];
                        upvector[1] = -gravityvector[1];
                        upvector[2] = -gravityvector[2];
                    }
                }
                if (!cbf_cistrcmp(axis_id,"UP")) {
                    if (CBF_SUCCESS== error) {
                        afound[6] = 1;
                        upvector[0] = cbfvector[0];
                        upvector[1] = cbfvector[1];
                        upvector[2] = cbfvector[2];
                        gravityvector[0] = -upvector[0];
                        gravityvector[1] = -upvector[1];
                        gravityvector[2] = -upvector[2];
                    }
                }

                
            } else {
                
                double cbfvector[3];
                
                axis_id = anames[row-rows];
                depends_on = ".";
                equipment = "general";
                rotation_axis = ".";
                rotation = 0.;
                system = "McStas_absolute";
                type = "general";
                offset[0] = offset[1] = offset[2] = 0.;
                                
                switch (row-rows) {
                    case 0:
                        cbfvector[0] = 1.;
                        cbfvector[1] = 0.;
                        cbfvector[2] = 0.;
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 1:
                        cbfvector[0] = 0.;
                        cbfvector[1] = 1.;
                        cbfvector[2] = 0.;
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 2:
                        cbfvector[0] = 0.;
                        cbfvector[1] = 0.;
                        cbfvector[2] = 1.;
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 3: /* BEAM */
                        if (afound[3] || afound[4])
                        {
                            cbfvector[0] = beamvector[0];
                            cbfvector[1] = beamvector[1];
                            cbfvector[2] = beamvector[2];
                        } else {
                            cbfvector[0] = 0.;
                            cbfvector[1] = 0.;
                            cbfvector[2] = -1.;
                        }
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 4: /* SOURCE */
                        if (afound[3] || afound[4]){
                            cbfvector[0] = sourcevector[0];
                            cbfvector[1] = sourcevector[1];
                            cbfvector[2] = sourcevector[2];
                        } else {
                            cbfvector[0] = 0.;
                            cbfvector[1] = 0.;
                            cbfvector[2] = 1.;
                        }
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 5: /* GRAVITY */
                        if (afound[5] || afound[6] ) {
                            cbfvector[0] = gravityvector[0];
                            cbfvector[1] = gravityvector[1];
                            cbfvector[2] = gravityvector[2];
                        } else {
                            cbfvector[0] = 0.;
                            cbfvector[1] = -1.;
                            cbfvector[2] = 0.;
                        }
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    case 6: /* UP */
                        if (afound[5] || afound[6]) {
                            cbfvector[0] = upvector[0];
                            cbfvector[1] = upvector[1];
                            cbfvector[2] = upvector[2];
                        } else {
                            cbfvector[0] = 0.;
                            cbfvector[1] = 1.;
                            cbfvector[2] = 0.;
                        }
                        CBF_CALL(cbf_apply_matrix(matrix,cbfvector,vector));
                        break;
                    default:
                        continue;
                }
                
                cbf_debug_print3("processing axis %s for equipment %s\n",axis_id,equipment);
            }
            
            CBF_CALL(cbf_H5Drequire(poise,&dset,axis_id,1,max,cnk,buf,H5T_IEEE_F64LE));
            CBF_CALL(cbf_H5Arequire_string(dset,"depends_on",depends_on));
            CBF_CALL(cbf_H5Arequire_string(dset,"equipment",equipment));
            CBF_CALL(cbf_H5Arequire_string(dset,"transformation_type",type));
            CBF_CALL(cbf_H5Arequire_string(dset,"system",system));
            if (cbf_cistrcmp(rotation_axis,".")) {
                CBF_CALL(cbf_H5Arequire_string(dset,"rotation_axis",rotation_axis));
                if (!error) {
                    /* write the rotation */
                    const hsize_t dim[] = {1};
                    double buf[] = {0};
                    if (H5Aexists(dset,"rotation") > 0) {
                        H5Adelete_by_name(dset,".","rotation",H5P_DEFAULT);
                    }
                    CBF_CALL(CBFM_H5Arequire_cmp2(dset,"rotation",1,dim,H5T_IEEE_F64LE,
                                                  H5T_NATIVE_DOUBLE,&rotation,buf,
                                                  cmp_double,cmp_params));
                    CBF_CALL(cbf_H5Arequire_string(dset,"rotation_units","degrees"));
                }
            }
            
            if (!error && cbf_norm(offset) > 1.e-20) {
                /* write the offset */
                const hsize_t dim[] = {3};
                double buf[] = {0};
                if (H5Aexists(dset,"offset") > 0) {
                    H5Adelete_by_name(dset,".","offset",H5P_DEFAULT);
                }
                CBF_CALL(CBFM_H5Arequire_cmp2(dset,"offset",1,dim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,offset,buf,cmp_double,cmp_params));
                CBF_CALL(cbf_H5Arequire_string(dset,"offset_units","mm"));
            }
            if (!error) {
                /* write the vector */
                const hsize_t dim[] = {3};
                double buf[] = {0};
                if (H5Aexists(dset,"vector") > 0) {
                    H5Adelete_by_name(dset,".","vector",H5P_DEFAULT);
                }
                CBF_CALL(CBFM_H5Arequire_cmp2(dset,"vector",1,dim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,vector,buf,cmp_double,cmp_params));
            }
            
            cbf_H5Dfree(dset);
        }
        cbf_H5Gfree(poise);
        return error;
    }

    
    /*
	Special function to handle axis conversions by dealing with axis sets and
	traversing the dependency chain for all referenced leaf axes. This doesn't
	match a set of rows within the axis table, so should not be forced into
	the same processing model as the conversion functions which do.

	See comments for a description of what this function does.
                 */
    static int cbf_write_cbf2nx__axis
                    (cbf_handle handle,
                     cbf_h5handle h5handle,
                     cbf_cbf2nx_key_t * const key,
                     const int list)
	{
		int error = CBF_SUCCESS;
        const char categoryName[] = "axis";
#ifdef CBF_USE_ULP
        cmp_double_param_t cmp_double_params;
        void * cmp_params = &cmp_double_params;
        
        /* set up the comparison parameters */
        cmp_double_params.cmp_double_as_float = cbf_has_ULP64() ? h5handle->cmp_double_as_float : 1;
        cmp_double_params.ulp32 = h5handle->float_ulp;
#ifndef NO_UINT64_TYPE
        cmp_double_params.ulp64 = h5handle->double_ulp;
#endif
#else
        void * cmp_params = 0;
        CBF_UNUSED(cmp_params);
#endif
        
		/* check arguments */
		if (!handle) {
            cbf_debug_print("Invalid handle given\n");
            error |= CBF_ARGUMENT;
        } else if (!h5handle) {
            cbf_debug_print("Invalid hdf5 handle given\n");
            error |= CBF_ARGUMENT;
        } else if (!key) {
            cbf_debug_print("Bad key given\n");
            error |= CBF_ARGUMENT;
        }else if (CBF_SUCCESS!=(error|=cbf_find_category(handle,categoryName))) {
            cbf_debug_print2("error: %s\n",cbf_strerror(error));
        } else {
            /* The axes in key->axis are used within the scan, so I must convert them all and any axes that they depend on. */
            cbf_node * const category = handle->node;
            unsigned int matched = 0;
            unsigned int i;
            if (h5handle->logfile) _cbf_write_name(h5handle->logfile,categoryName,0,key->indent,1);
            if (key->categories) {
                cbf_node * * it;
                cbf_node * const * const end = key->nCat+key->categories;
                for (it = key->categories; end != it; ++it) {
                    if (*it) {
                        *it = strcmp((*it)->name,categoryName) ? *it : NULL;
                    }
                }
            }
            /*
             Each axis set may contain multiple axes. Each of these needs to have its full dependency chain recorded. I
             should not generate any new axes for any axis within an axis set, but should add all parent axes that are
             not in an axis set. The creation of an axis for the axis set is not the responsibility of this function.
             */
            {
                cbf_node * asla_setid = NULL;
                cbf_node * asla_axisid = NULL;
                cbf_node * axis_id = NULL;
                cbf_node * axis_depends_on = NULL;
                cbf_node * axis_rotation_axis = NULL;
                CBF_CALL(cbf_find_category(handle,"array_structure_list_axis"));
                CBF_CALL(cbf_find_child(&asla_setid,handle->node,"axis_set_id"));
                CBF_CALL(cbf_find_child(&asla_axisid,handle->node,"axis_id"));
                CBF_CALL(cbf_find_category(handle,"axis"));
                CBF_CALL(cbf_find_child(&axis_id,handle->node,"id"));
                if(cbf_find_child(&axis_depends_on,handle->node,"depends_on")) {
                    axis_depends_on = NULL;
                };
                if(cbf_find_child(&axis_depends_on,handle->node,"rotation_axis")) {
                    axis_rotation_axis = NULL;
                };
                
                if (CBF_SUCCESS==error) {
                    unsigned int i;
                    unsigned int nAxes = 0;
                    const char * * axes = NULL;
                    /* 1. get a list of all axes within a valid axis set */
                    for (i = 0; i != key->arrayAxisSet.count; ++i) {
                        unsigned int j = 0;
                        /* loop over ASLA to locate matching axis_set_id, store corresponding axis_id if it isn't already present */
                        for (j = 0; j != asla_setid->children; ++j) {
                            const char * axis = NULL;
                            const char * set = NULL;
                            CBF_CALL(cbf_node_get_value(asla_setid,j,&set));
                            CBF_CALL(cbf_node_get_value(asla_axisid,j,&axis));
                            if (h5handle->logfile) fprintf(h5handle->logfile,"axis: '%s'\n",axis);
                            if (h5handle->logfile) fprintf(h5handle->logfile,"set: '%s'\n",set);
                            if (CBF_SUCCESS==error) {
                                if (strcmp(set,key->arrayAxisSet.axis_set_id[i])) {
                                    continue;
                                } else {
                                    unsigned int k = 0;
                                    /* I have an axis id from the current set, ensure it exists within the axis list */
                                    for (k = 0; k != nAxes; ++k) {
                                        if (!strcmp(axis,axes[k])) break;
                                    }
                                    if (k == nAxes) {
                                        const char * * newAxes = NULL;
                                        /* axis id wasn't found in the set - add it */
                                        ++nAxes;
                                        if (!(newAxes=realloc(axes,sizeof(const char *)*nAxes))) {
                                            cbf_debug_print2("error: %s\n",cbf_strerror(CBF_ALLOC));
                                            error |= CBF_ALLOC;
                                        } else {
                                            axes[nAxes-1] = axis;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    /*
                     2. check dependency chain for each axis in axes, if the parent
                     axis is not in axes or in key->axis then add it to key->axis
                     */
                    for (i = 0; i != nAxes; ++i) {
                        const char * depends_on = NULL;
                        if (CBF_SUCCESS!=(error|=cbf_node_get_value(axis_depends_on,i,&depends_on))) {
                            cbf_debug_print2("error: %s\n",cbf_strerror(error));
						} else {
                            unsigned int j = 0;
                            unsigned int k = 0;
                            for (j = 0; j != nAxes; ++j) {
                                if (i != j && !strcmp(depends_on,axes[j])) {
                                    break;
                                }
                            }
                            for (k = 0; k != key->axis.count; ++k) {
                                if (!strcmp(depends_on,key->axis.axis_id[k])) {
                                    break;
                                }
                            }
                            if (j == nAxes && k == key->axis.count) {
                                /*
                                 The parent axis for CBF's axis[i] is not listed as part of an axis set for the current scan,
                                 or as one of the axes that have already been mapped. Need to add it - and any unlisted parent
                                 axes - to the list of axes that must be mapped.
                                 TODO: implement this
                                 */
                                cbf_debug_print2("error: %s\n",cbf_strerror(CBF_NOTIMPLEMENTED));
                                error |= CBF_NOTIMPLEMENTED;
                            }
                        }
                    }
                    free((void*)axes);
                }
            }
            /* convert each axis: */
            for (i = 0; CBF_SUCCESS==error && i != key->axis.count; ++i) {
                const char * axis_name = key->axis.axis_id[i];
                const char * axis_rot_name = NULL;
                const char * axis_path = key->axis.path[i];
                const char * axis_rot_path = NULL;
                const char axis_root[] = ".";
                while (CBF_SUCCESS==error && axis_name && strcmp(axis_name,".") && axis_path) {
                    hid_t dset = CBF_H5FAIL;
                    const hsize_t max[] = {H5S_UNLIMITED};
                    const hsize_t cnk[] = {1};
                    hsize_t buf[] = {0};
                    CBF_CALL(cbf_H5Drequire(h5handle->hfile,&dset,axis_path,1,max,cnk,buf,H5T_IEEE_F64LE));
                    CBF_CALL(cbf_find_column(handle,"id"));
                    CBF_CALL(cbf_find_row(handle,axis_name));
                    if (CBF_SUCCESS==error) {
						cbf_axis_data_t axis_settings = cbf_axis_data_init();
						cbf_read_axis_row(&axis_settings,category,handle->row);
                        ++matched;
                        /* update variables for next iteration & to record the axis dependency */
						axis_name = axis_settings.depends_on;
                        if (!axis_name || !strcmp(axis_name,axis_root)
                            || !strcmp(axis_name,"?") || !strcmp(axis_name,".")) {
                            axis_path = axis_root;
                        } else {
                            unsigned int j;
                            for (j = 0; j != key->axis.count; ++j) {
                                if (!cbf_cistrcmp(key->axis.axis_id[j],axis_name)) break;
                            }
                            if (j != key->axis.count) {
                                /* assign existing axis path */
                                axis_path = key->axis.path[j];
                            } else {
                                /* TODO: make up a new axis path & store it for future reference */
                                axis_path = NULL;
                                cbf_debug_print("conversion of axes not in detector or goniometer axis groups is not implemented - need to define a path for them\n");
                                cbf_debug_print2("problematic axus %s\n",axis_name);
                                error |= CBF_NOTIMPLEMENTED;
                            }
                        }
                        axis_rot_name = axis_settings.rotation_axis;
                        if (!axis_rot_name || !strcmp(axis_rot_name,axis_root)
                            || !strcmp(axis_rot_name,"?")|| !strcmp(axis_rot_name,".")) {
                            axis_rot_path = NULL;
                        } else {
                            unsigned int j;
                            for (j = 0; j != key->axis.count; ++j) {
                                if (!strcmp(key->axis.axis_id[j],axis_rot_name)) break;
                            }
                            if (j != key->axis.count) {
                                /* assign existing axis path */
                                axis_rot_path = key->axis.path[j];
                            } else {
                                /* TODO: make up a new axis path & store it for future reference */
                                axis_rot_path = NULL;
                                cbf_debug_print("conversion of axes not in detector or goniometer axis groups is not implemented - need to define a path for them\n");
                                cbf_debug_print2("problematic axis %s\n",axis_name);
                                error |= CBF_NOTIMPLEMENTED;
                            }
                        }
                        
                        /* I might have the data - write it to HDF5 if I do */
                        if (CBF_SUCCESS==error) {
                            /* write the dependency */
                            if (axis_path) {
                                CBF_CALL(cbf_H5Arequire_string(dset,"depends_on",axis_path));
                            } else {
                                CBF_CALL(cbf_H5Arequire_string(dset,"depends_on","?"));
                            }
                            /* write the equipment */
							if (axis_settings.equipment) CBF_CALL(cbf_H5Arequire_string(dset,"equipment",axis_settings.equipment));
                            if (axis_settings.equipment_component) CBF_CALL(cbf_H5Arequire_string(dset,"equipment_component",axis_settings.equipment_component));
                            if (axis_rot_path) {
                                CBF_CALL(cbf_H5Arequire_string(dset,"rotation_axis",axis_rot_path));
                                const hsize_t dim[] = {1};
                                double buf[] = {0};
                                CBF_CALL(CBFM_H5Arequire_cmp2(dset,"",1,dim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,&(axis_settings.rotation),buf,cmp_double,cmp_params));
                                CBF_CALL(cbf_H5Arequire_string(dset,"rotation_units","degrees"));
                            }
                            if (!error) {
                                /* write the offset */
								double offset[3] = {0.,0.,0.};
                                const hsize_t dim[] = {3};
                                double buf[] = {0};
								if (3==axis_settings.nOffset) {
                                    CBF_CALL(cbf_apply_matrix(key->matrix,axis_settings.offset,offset));
                                }
                                CBF_CALL(CBFM_H5Arequire_cmp2(dset,"offset",1,dim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,offset,buf,cmp_double,cmp_params));
                                CBF_CALL(cbf_H5Arequire_string(dset,"offset_units","mm"));
                            }
                            /* write the type */
                            if (axis_settings.type) {
                                if (CBF_SUCCESS!=(error|=cbf_H5Arequire_string(dset,"transformation_type",axis_settings.type))) {
                                    cbf_debug_print2("error: %s\n",cbf_strerror(error));
                                } else {
                                    if (!strcmp(axis_settings.type,"translation")) {
                                        CBF_CALL(cbf_H5Arequire_string(dset,"units","mm"));
                                    } else if (!strcmp(axis_settings.type,"rotation")){
                                        CBF_CALL(cbf_H5Arequire_string(dset,"units","degrees"));
                                    } else {
                                        cbf_debug_print2("error: unrecognised axis type: %s\n",axis_settings.type);
                                        error |= CBF_UNDEFINED;
                                    }
                                }
                            }
                            if (!error) {
                                /* write the vector */
								double vector[3] = {0.,0.,0.};
                                const hsize_t dim[] = {3};
                                double buf[] = {0};
                                if (3==axis_settings.nVector) {
                                    CBF_CALL(cbf_apply_matrix(key->matrix,axis_settings.vector,vector));
                                }
                                if (H5Aexists(dset,"vector") > 0) {
                                    H5Adelete_by_name(dset,".","vector",H5P_DEFAULT);
                                }
                                CBF_CALL(CBFM_H5Arequire_cmp2(dset,"vector",1,dim,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,vector,buf,cmp_double,cmp_params));
                            }
                        }
                    }
                    cbf_H5Dfree(dset);
                }
            }
        }
		return error;
	}

	/*
	Create an 'NXdata' class and ensure it contains links to existing data within the
	rest of the entry group, to allow automatic visualisation. The paths for existing
	links are not checked.
	*/
    static int cbf_write_cbf2nx__link_h5data
			(cbf_handle handle,
     cbf_h5handle h5handle)
	{
		int error = CBF_SUCCESS;

		cbf_debug_print("link_h5data\n");

		/* check arguments */
		if (!handle) {
            cbf_debug_print("Invalid handle given\n");
            error |= CBF_ARGUMENT;
        } else if (!h5handle) {
            cbf_debug_print("Invalid hdf5 handle given\n");
            error |= CBF_ARGUMENT;
        } else {
		/* ensure an entry/data group exists and has a link to the dataset */
		if (!cbf_H5Ivalid(h5handle->nxdata)) {
                CBF_CALL(cbf_H5Grequire(h5handle->nxid,&h5handle->nxdata,"data"));
		}
		/* use it to link to data */
		if (CBF_SUCCESS==error && cbf_H5Ivalid(h5handle->nxdata)) {
			const htri_t data_exists = H5Lexists(h5handle->nxdata,"data",H5P_DEFAULT);
			const htri_t data_scaling_exists = H5Lexists(h5handle->nxdetectors[h5handle->cur_detector],
                                                         "scaling_factor",H5P_DEFAULT);
			const htri_t data_offset_exists = H5Lexists(h5handle->nxdetectors[h5handle->cur_detector],
                                                        "offset",H5P_DEFAULT);
                CBF_CALL(cbf_H5Arequire_string(h5handle->nxdata,"NX_class","NXdata"));
                CBF_CALL(cbf_H5Arequire_string(h5handle->nxdata,"signal","data"));
			if (data_exists < 0) {
				error |= CBF_H5ERROR;
			} else if (data_exists) {
				/* it exists - done */
			} else {
				H5Lcreate_hard(h5handle->nxdetectors[h5handle->cur_detector],
                               "data",h5handle->nxdata,"data",H5P_DEFAULT,H5P_DEFAULT);
			}
			if (data_scaling_exists < 0) {
				error |= CBF_H5ERROR;
			} else if (data_scaling_exists) {
				const htri_t scaling_exists = H5Lexists(h5handle->nxdata,"scaling_factor",H5P_DEFAULT);
				if (scaling_exists < 0) {
					error |= CBF_H5ERROR;
				} else if(scaling_exists) {
					/* it exists - done */
				} else {
					H5Lcreate_hard(h5handle->nxdetectors[h5handle->cur_detector],
                                   "scaling_factor",
								   h5handle->nxdata,"scaling_factor",
								   H5P_DEFAULT,H5P_DEFAULT);
				}
			} else {
				/* I don't need to link to it - done */
			}
			if (data_offset_exists < 0) {
				error |= CBF_H5ERROR;
			} else if (data_offset_exists) {
				const htri_t offset_exists = H5Lexists(h5handle->nxdata,"offset",H5P_DEFAULT);
				if (offset_exists < 0) {
					error |= CBF_H5ERROR;
				} else if(offset_exists) {
					/* it exists - done */
				} else {
					H5Lcreate_hard(h5handle->nxdetectors[h5handle->cur_detector],
                                   "offset",
								   h5handle->nxdata,"offset",
								   H5P_DEFAULT,H5P_DEFAULT);
				}
			} else {
				/* I don't need to link to it - done */
			}

			/* extract some axes based on the scan type */
                if (CBF_SUCCESS==error) {
                    const htri_t axis_fast_exists = H5Lexists(h5handle->nxdetectors[h5handle->cur_detector],
                                                              "y_pixel_offset",H5P_DEFAULT);
                    const htri_t axis_slow_exists = H5Lexists(h5handle->nxdetectors[h5handle->cur_detector],
                                                              "x_pixel_offset",H5P_DEFAULT);
				if (axis_fast_exists < 0) {
					error |= CBF_H5ERROR;
				} else if (axis_fast_exists) {
					const htri_t axis_exists = H5Lexists(h5handle->nxdata,"y",H5P_DEFAULT);
					if (axis_exists < 0) {
						error |= CBF_H5ERROR;
					} else if(axis_exists) {
						/* it exists - done */
					} else {
                            H5Lcreate_hard(h5handle->nxdetectors[h5handle->cur_detector],
                                           "y_pixel_offset",
									   h5handle->nxdata,"y",
									   H5P_DEFAULT,H5P_DEFAULT);
					}
				} else {
					/* I can't need to link to it - complain & fail */
                        cbf_debug_print("Error: cannot find axis data\n");
					error |= CBF_UNDEFINED;
				}
				if (axis_slow_exists < 0) {
					error |= CBF_H5ERROR;
				} else if (axis_slow_exists) {
					const htri_t axis_exists = H5Lexists(h5handle->nxdata,"x",H5P_DEFAULT);
					if (axis_exists < 0) {
						error |= CBF_H5ERROR;
					} else if(axis_exists) {
						/* it exists - done */
					} else {
                            H5Lcreate_hard(h5handle->nxdetectors[h5handle->cur_detector],
                                           "x_pixel_offset",
									   h5handle->nxdata,"x",
									   H5P_DEFAULT,H5P_DEFAULT);
					}
				} else {
					/* I can't need to link to it - complain & fail */
                        cbf_debug_print("Error: cannot find axis data\n");
					error |= CBF_UNDEFINED;
				}
                    if (CBF_SUCCESS==error) { /* axes=[slow_dim, ..., fast_dim] */
					hid_t h5atype = CBF_H5FAIL;
					const char axis0[] = "";
                        const char axis1[] = "y";
                        const char axis2[] = "x";
					const char * axes[] = {axis0,axis1,axis2};
					const hsize_t dim[] = {3};
					char * buf[3] = {0};
                        CBF_CALL(cbf_H5Tcreate_string(&h5atype,H5T_VARIABLE));
                        CBF_CALL(CBFM_H5Arequire_cmp2(h5handle->nxdata,"axes",1,dim,h5atype,h5atype,axes,buf,cmp_vlstring,0));
					cbf_H5Tfree(h5atype);
				}
                    if (CBF_SUCCESS==error) {
                        const char x_indices[] = "x_indices";
                        const char y_indices[] = "y_indices";
                        const char * indices[] = {
                            y_indices,
                            x_indices,
                        };
                        const int idx[] = {1,2};
                        int i;
                        for (i = 0; i != 2; ++i) {
					int buf[] = {0};
                            CBF_CALL(
                                     CBFM_H5Arequire_cmp2(
                                                             h5handle->nxdata,
                                                             indices[i],
                                                             0,
                                                             0,
                                                             H5T_STD_I32LE,
                                                             H5T_NATIVE_INT,
                                                             i+idx,
                                                             buf,
                                                             cmp_int,
                                                             0
                                                             )
                                     );
				}
				}
                }
            }
        }
        return error;
    }
    
    /*
	Parametric conversion of data within a sebset of the rows of a single table.
    
	Note: This accesses (read-only) global state in the form of a table which gives data about mappings.
    
	Data is extracted and converted by:
	Direct conversion from a single CBF data item to a single NeXus data item.
	Collecting information from each column within a single matching row, then processing it in some way.
	Collecting information from each matching row within a single table, then processing it in some way.
    
	In complex cases, this _should_ involve collecting data in a per-row cache,
	then adding it to a per-table cache, then adding it to the higher-level
	'key' object. This is by design, to allow suitable processing to be
	inserted in between each level in order to ensure data integrity and
	perform format conversions and carry out memory management as needed.

	This is done by performing the following operations:
	- Locate the category requested and the mapping data for it. An
	error will occur if either isn't found.
	- Data about the primary keys of the table must be populated, to be used
	when matching rows and iterating through columns.
	- A set of matching rows is extracted from the table.
	- create a table-specific cache object
	- foreach matching row {
	- create a row-specific cache object
	- foreach column {
	either {
	- filter data value
	- store in nexus file
} or {
	- cache value as a key to be used later
} or {
	- cache value in per-row cache object
                    }
                }
	- process row-specific cache object, which may involve writing data
	to the nexus file or storing it in a table-specific cache object.
	- destroy the row-specific cache object
            }
	- process and then destroy the table-specific cache object

	This should be used by:
	- defining a set of primary key columns and telling the program how to get at their values.
	- defining a set of filter functions which may be used when converting data items directly.
	- defining a set of cache objects and functions to populate and process them.
	- gluing everything together with mapping tables in a pre-defined format.

	Future extensions:
	Replace the whole data conversion model/pipeline with a more powerful dRel-based model.
     */
	static int cbf2nx_convert_category
                    (cbf_node * const node /*< the datablock being converted */,
                     cbf_h5handle nx /*< the nexus file to store it in */,
                     const char * const categoryName /*< the category to convert */,
                     cbf_cbf2nx_key_t * const key /*< a higher-level cache of values to control the conversion */,
                     const int list /*< boolean: list items or not? */,
                     const int required /*< boolean: is this category required for success? */)
    {
        int error = CBF_SUCCESS;
        unsigned int matched = 0;

        /* check arguments */
        if (!node) {
            cbf_debug_print2("error: %s\n","Invalid cbf node given\n");
            error |= CBF_ARGUMENT;
		} else if (CBF_DATABLOCK != node->type) {
			cbf_debug_print2("error: %s\n","cbf node is not a datablock");
            error |= CBF_ARGUMENT;
		} else if (!nx) {
            cbf_debug_print2("error: %s\n","Invalid hdf5 handle given");
			error |= CBF_ARGUMENT;
		} else if (!categoryName) {
			cbf_debug_print2("error: %s\n","No category specified");
			error |= CBF_ARGUMENT;
        } else if (!key) {
            cbf_debug_print2("error: %s\n","Bad key given\n");
            error |= CBF_ARGUMENT;
        } else {
			/* arguments are fine, try to get a category to use and mappings to convert it */
			cbf_node * category = NULL;
			const cbf2nx_category_map_t * const category_map = cbf2nx_find_category_mapping(cbf_map,categoryName);
			const int found = cbf_find_child(&category,node,categoryName);
			if (!category_map) {
                cbf_debug_print("error: No mapping located for category");
				error |= CBF_NOTFOUND;
			}
			if (CBF_NOTFOUND==found) {
				if (required) {
					cbf_debug_print("error: required category not found");
					error |= CBF_NOTFOUND;
				}
			} else if (found) {
                cbf_debug_print2("error: %s\n",cbf_strerror(found));
				error |= found;
			}
			if (category && !error) {
				/* I have a category and the conversions for it, apply them */
            unsigned int * rows = NULL;
            unsigned int row = 0, nRows = 0, mRows = 0;
            unsigned int indent = 1+key->indent;
				cbf_node * * primary_key_column = NULL;
				const char * * primary_key_value = NULL;
				/* allocate cache objects */
				void * const row_cache = category_map->row_cache.size ? malloc(category_map->row_cache.size) : NULL;
				void * const tbl_cache = category_map->tbl_cache.size ? malloc(category_map->tbl_cache.size) : NULL;
				if (tbl_cache && category_map->tbl_cache.ctor) CBF_CALL(category_map->tbl_cache.ctor(tbl_cache));
            /* record that the category is recognised */
                if (nx->logfile) _cbf_write_name(nx->logfile,category->name,0,key->indent,1);
            CBF_CALL(_cbf2nx_key_remove_category(key,category->name));
            /* check that I have some children, and try to find the primary key columns */
            if (0==category->children) {
                cbf_debug_print2("error: %s\n","category has no children");
                error |= CBF_NOTFOUND;
            } else {
                nRows = category->child[0]->children;
					CBF_CALL(cbf_populate_primaryKey_cache(category_map->key_data,&primary_key_column,&primary_key_value,key,category));
            }
				/* ensure I have at least one matching row */
				CBF_CALL(cbf_get_matching_rows(category_map->key_data,primary_key_column,primary_key_value,nRows,&rows,&mRows));
            if (0==mRows) {
                cbf_debug_print2("error: %s\n","No matching data located");
                error |= CBF_FORMAT;
            }
				/*
				iterate over matching rows and over each column in each matching
				row, calling a function to convert or cache the data.
				*/
            for (row = 0; !error && row != mRows; ++row) {
                cbf_node * const * column_it;
					if (row_cache && category_map->row_cache.ctor) CBF_CALL(category_map->row_cache.ctor(row_cache));
                for (column_it = category->child; !error && column_it != category->children+category->child; ++column_it) {
                    cbf_node * const column = *column_it;
						if (array_contains((const void * const *)primary_key_column,cbf_count_primary_keys(category_map->key_data),column)) {
                            if (nx->logfile && !matched) _cbf_write_name(nx->logfile,column->name,0,indent,1);
                        } else {
							CBF_CALL(cbf2nx_apply_conversions(nx,key,category_map->column_data,column,row,row_cache,list,matched));
                        }
                                }
                ++matched;
					/* use cache object */
					if (row_cache && category_map->process_row) CBF_CALL(category_map->process_row(category,nx,key,row_cache,tbl_cache,row));
					/* clear out old data, leaving the cache ready to be re-used or disposed of */
					if (row_cache && category_map->row_cache.dtor) CBF_CALL(category_map->row_cache.dtor(row_cache));
            }
            if (!matched) {
                /* TODO: in some cases this will be an error, find them */
                cbf_debug_print("warning: No data located");
            }
				/* use cache object */
				if (tbl_cache && category_map->process_tbl) CBF_CALL(category_map->process_tbl(category,nx,key,tbl_cache));
				/* clear out old data, leaving the cache ready to be re-used or disposed of */
				if (tbl_cache && category_map->tbl_cache.dtor) CBF_CALL(category_map->tbl_cache.dtor(tbl_cache));
				/* clean up */
				free(row_cache);
				free(tbl_cache);
            free((void*)rows);
				free((void*)primary_key_column);
				free((void*)primary_key_value);
        }
    }
		if (error && categoryName) {
           cbf_debug_print(categoryName);
		}
        return error;
    }
    
    /**
     Equivalent to <code>cbf_write_cbf2nx(handle,h5handle,0,0,0)</code>.

     \param handle The CBF file to extract data from.
     \param h5handle The NeXuS file to write data to.
     \sa cbf_write_cbf_h5file
     \sa cbf_write_minicbf_h5file
     \sa cbf_write_cbf2nx
     \sa cbf_write_nx2cbf
     \return An error code.
	*/
	int cbf_write_cbf_h5file
			(cbf_handle handle,
			 cbf_h5handle h5handle)
	{
        return cbf_write_cbf2nx(handle,h5handle,0,0,0);
    }
    
    /**
     Extracts data from <code>handle</code> and generates a NeXus file in <code>h5handle</code>. This will attempt
     to extract metadata and image data from each scan (or the named scan) within each datablock (or the the named
     datablock) and insert it into a given index into the NXentry group specified in <code>h5handle</code>.
     
     Each scan in the CBF file corresponds to one NXentry in NeXus, so a CBF datablock with multiple scans must be
     converted by calling this function with the appropriate value of <code>scan</code> once for each scan in the
     datablock.
     
     The flags (within <code>h5handle</code>) determine:
     
     - Compression algorithm: zlib/CBF/none
     - Plugin registration method: automatic/manual
     
     The strings given by <code>h5handle->scan_id</code> and <code>h5handle->sample_id</code> define:
     
     - The presence and value of an identifier for the scan, stored in <code>/\*:NXentry/entry_identifier</code>.
     - The presence and value of an identifier for the sample, stored in <code>/\*:NXentry/\*:NXsample/sample_identifier</code>.
     
     \sa cbf_write_cbf_h5file
     \sa cbf_write_minicbf_h5file
     \sa cbf_write_nx2cbf
     \return An error code.
     */
    int cbf_write_cbf2nx
			(cbf_handle handle /**< The CBF file to extract data from. */,
			 cbf_h5handle h5handle /**< The NeXuS file to write data to. */,
			 const char * const datablock /**< The name of the datablock to convert, or NULL to convert all datablocks. */,
			 const char * const scan /**< The name of the scan to convert, or NULL if there is only one scan in the datablock. */,
			 const int list /**< Boolean flag to determine if a list of processed items is printed. */)
    {
        int error = CBF_SUCCESS;
        int found = CBF_SUCCESS;
        cbf_cbf2nx_key_t key[1];
		cbf_node *node = NULL;
		cbf_node * db = NULL;
		hid_t detector = CBF_H5FAIL, instrument = CBF_H5FAIL; /* do not free */

        /* check arguments */
        if (!handle || !h5handle) return CBF_ARGUMENT;
        
        /* initialise local variables */
        *key = _cbf_make_cbf2nx_key();
        
		/* ensure the handle contains some basic structure */
        CBF_CALL(cbf_h5handle_require_entry(h5handle,0,0));
        CBF_CALL(cbf_h5handle_require_instrument(h5handle,&instrument,0));
        if (h5handle->flags & CBF_H5_CBFNONAMES) {
            CBF_CALL(cbf_h5handle_require_detector(h5handle,&detector,0));
        } else {
            CBF_CALL(cbf_require_nxdetectors(handle,h5handle));
            detector = h5handle->nxdetectors[h5handle->cur_detector];
        }

        if (h5handle->scan_id) {
            CBF_CALL(cbf_H5Drequire_flstring(h5handle->nxid,0,"entry_identifier",h5handle->scan_id));
        }

        if (h5handle->sample_id) {
            hid_t sample = CBF_H5FAIL;
            CBF_CALL(cbf_h5handle_require_sample(h5handle,&sample,0));
            CBF_CALL(cbf_H5Drequire_flstring(h5handle->nxsample,0,"sample_identifier",h5handle->sample_id));
        }
        
		/* prepare the CBF handle */
        CBF_CALL(cbf_reset_refcounts(handle->dictionary));
        CBF_CALL(cbf_find_parent(&node, handle->node, CBF_ROOT));

        /* either select the requested datablock or the first datablock */
        if (datablock) {
            CBF_CALL(cbf_find_datablock(handle,datablock));
        } else {
            CBF_CALL(cbf_rewind_datablock(handle));
        }
        db = handle->node;
        
			/*
         Process the current datablock, if valid.
         Must have a valid datablock selected when entering this loop.
			*/
        while (CBF_SUCCESS==error) {
            unsigned int nCat = 0;
            cbf_node * * categories = NULL;
            cbf_node * scans = NULL;
            CBF_CALL(cbf_count_categories(handle,&nCat));
            if (!(categories=malloc(sizeof(cbf_node*)*nCat))) {
                cbf_debug_print2("error: %s\n",cbf_strerror(CBF_ALLOC));
                error |= CBF_ALLOC;
				} else {
                memcpy(categories,handle->node->child,sizeof(cbf_node*)*nCat);
                key->categories = categories;
                key->nCat = nCat;
				}
            if (h5handle->logfile) {
                int printed = 0;
                fputc('\n',h5handle->logfile);
                printed = fprintf(h5handle->logfile,"Datablock: %s\n",handle->node->name);
                while (--printed > 0) fputc('=',h5handle->logfile);
                fputc('\n',h5handle->logfile);
                fputc('\n',h5handle->logfile);
			}
			/* get the axis transformation matrix, which is constant within a datablock */
            CBF_CALL(cbf_get_NX_axis_transform(handle,key->matrix));
            /* Get the list of scans */
            CBF_CALL(cbf_find_category(handle, "diffrn_scan"));
            CBF_CALL(cbf_rewind_column(handle));
            CBF_CALL(cbf_count_rows(handle, &key->nScans));
            /* get the first/requested/only scan id, depending on arguments given */
            found = cbf_find_column(handle, "id");
            if (CBF_NOTFOUND==found) {
                if (1 != key->nScans) {
                    /* unindexed scan ids => error */
                    cbf_debug_print("error: found multiple scans but no 'diffrn_scan.id'");
                    error |= CBF_FORMAT;
						}
            } else if (CBF_SUCCESS!=found) {
                cbf_debug_print2("error: %s\n",cbf_strerror(found));
                error |= found;
					} else {
                scans = handle->node;
                /* select the named/first scan */
                if (scan) {
                    CBF_CALL(cbf_find_row(handle,scan));
                } else {
                    CBF_CALL(cbf_rewind_row(handle));
					}
                /* get the scan id */
                CBF_CALL(cbf_get_value(handle, &key->scan));
				}
            if (!scan && 1 != key->nScans) {
                cbf_debug_print("error: insufficient data to select a single scan");
                error |= CBF_ARGUMENT;
            }
            
					/*
             Convert the relevant scan.
					*/
					if (CBF_SUCCESS == error) {
                unsigned int frame_row = 0;
                unsigned int nFrames = 0;
                cbf_node * frames_scanid = NULL;
                if (h5handle->logfile) {
                    int printed = fprintf(h5handle->logfile,"Scan: %s\n",key->scan);
                    while (--printed > 0) fputc('-',h5handle->logfile);
                    fputc('\n',h5handle->logfile);
                    fputc('\n',h5handle->logfile);
						}
                /* convert the scan data */
				CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_scan", key, list, 1));
                /* get the list of frames */
                CBF_CALL(cbf_find_category(handle, "diffrn_scan_frame"));
                CBF_CALL(cbf_rewind_column(handle));
                CBF_CALL(cbf_count_rows(handle, &nFrames));
                /* get the scan id, if it exists */
                found = cbf_find_column(handle, "scan_id");
                if (CBF_NOTFOUND==found) {
                    if (scans && 1 != key->nScans) {
                        /* multiple unindexed frame ids => error */
                        cbf_debug_print("error: 'diffrn_scan_frame.scan_id' not found");
                        error |= found;
						} else {
                        cbf_debug_print("warning: 'diffrn_scan_frame.scan_id' not found");
						}
                } else if (CBF_SUCCESS!=found) {
                    cbf_debug_print2("error: %s\n",cbf_strerror(found));
                    error |= found;
								} else {
                    frames_scanid = handle->node;
								}
                /* select the first frame */
                CBF_CALL(cbf_rewind_row(handle));
                /* loop though all frames related to this scan */
                for (frame_row = 0; CBF_SUCCESS == error && nFrames != frame_row; ++frame_row) {
                    if (frames_scanid) {
                        const char * curr_scanid = NULL;
                        if (CBF_SUCCESS!=(error|=cbf_node_get_value(frames_scanid, frame_row, &curr_scanid))) {
                            cbf_debug_print2("error: %s\n",cbf_strerror(error));
                        } else if (strcmp(curr_scanid, key->scan)) {
                            continue;
								}
							}
                    _cbf_reset_cbf2nx_key(key);
                    /* get the frame id to work with */
                    CBF_CALL(cbf_find_category(handle, "diffrn_scan_frame"));
                    CBF_CALL(cbf_find_column(handle, "frame_id"));
                    CBF_CALL(cbf_select_row(handle,frame_row));
                    CBF_CALL(cbf_get_value(handle, &key->frame));
                    /* convert the row if the obtained scan value matches the expected value, always go to the next row */
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_scan_frame", key, list, 1));
                    /* navigate to the frame data & extract some IDs */
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_data_frame", key, list, 1));
                    /* convert the metadata */
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_detector_element", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_detector", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_detector_axis", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_source", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_measurement", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_measurement_axis", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_radiation", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_radiation_wavelength", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_refln", key, list, 0));
                    if (h5handle->flags & CBF_H5_CBFNONAMES) {
                    CBF_CALL(cbf_write_cbf2nx__axis(handle, h5handle, key, list));
                    CBF_CALL(cbf_write_cbf2nx__cbf_general_axes(handle, h5handle, key->matrix));
                    }
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_scan_axis", key, list, 0));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "diffrn_scan_frame_axis", key, list, 0));
                    /* convert the data */
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "array_intensities", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "array_data", key, list, 1));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "array_structure", key, list, 0));
					CBF_CALL(cbf2nx_convert_category(db, h5handle, "array_structure_list", key, list, 1));
                    CBF_CALL(cbf_write_cbf2nx__array_structure_list_axis(handle, h5handle, key, list));
                    if (h5handle->flags & CBF_H5_CBFNONAMES) {
                    CBF_CALL(cbf_write_cbf2nx__link_h5data(handle, h5handle));
                    }
                    ++h5handle->slice;
					}
					}
            
            if (CBF_SUCCESS==error && h5handle->logfile) {
                cbf_node * const * it;
                cbf_node * const * const end = nCat+categories;
                for (it = categories; end != it; ++it) {
                    if (*it) {
                        _cbf_write_name(h5handle->logfile,(*it)->name,0,0,0);
				}
			}
                fputc('\n',h5handle->logfile);
		}
            free((void*)categories);
            if (datablock) {
                /* the requested datablock has been processed - done */
                break;
            } else {
                /* go on to the next datablock */
                const int found = cbf_next_datablock(handle);
                if (CBF_NOTFOUND != found) error |= found;
                if (CBF_SUCCESS != found) break;
            }
        }

        _cbf_free_cbf2nx_key(*key);
		return error;
	}

    /**
     Extracts the miniCBF data directly - by parsing the header - and uses that plus the configuration options from
	<code>axisConfig</code> to generate a NeXus file in <code>h5handle</code>. This can extract metadata and image
	data from miniCBF files containing multiple datablocks which each contain a single image and insert it into a
     given index into the NXentry group specified in <code>h5handle</code>.

     Currently, only <code>Pilatus 1.2</code> format headers are supported.

     The flags determine:
     
     - Compression algorithm: zlib/CBF/none
     - Plugin registration method: automatic/manual
     
     \param handle The miniCBF file to extract data from.
     \param h5handle The NeXus file to write data to.
     \param axisConfig The configuration settings desribing the axes and their relation to the sample and to each other.
     \sa cbf_write_cbf_h5file
     \sa cbf_write_minicbf_h5file
     \sa cbf_write_nx2cbf
     \return An error code.
	*/
	int cbf_write_minicbf_h5file
		(cbf_handle handle,
		 cbf_h5handle h5handle,
		 const cbf_config_t * const axisConfig)
	{
		int error = CBF_SUCCESS;
		cbf_node *node = NULL;
		const char * saturation_value = NULL;
        hid_t detector = CBF_H5FAIL, instrument = CBF_H5FAIL; /* do not free */
#ifdef CBF_USE_ULP
		cmp_double_param_t cmp_double_params;
        void * cmp_params = &cmp_double_params;

		/* set up the comparison parameters */
		cmp_double_params.cmp_double_as_float = cbf_has_ULP64() ? h5handle->cmp_double_as_float : 1;
		cmp_double_params.ulp32 = h5handle->float_ulp;
#ifndef NO_UINT64_TYPE
		cmp_double_params.ulp64 = h5handle->double_ulp;
#endif
#else
        void * cmp_params = 0;
        CBF_UNUSED(cmp_params);
#endif


		if (!handle || !h5handle) return CBF_ARGUMENT;


		/* Find the root node */
		cbf_failnez (cbf_find_parent (&node, handle->node, CBF_ROOT));

		/* Reset the reference counts */
		cbf_failnez( cbf_reset_refcounts(handle->dictionary) );

		/* ensure the handle contains some basic structure */
        cbf_reportnez(cbf_h5handle_require_instrument(h5handle,&instrument,0), error);
		cbf_reportnez(cbf_h5handle_require_detector(h5handle,&detector,0), error);

		/* Do the mappings from CBF to nexus */
        cbf_onfailnez(error |= cbf_rewind_datablock(handle), cbf_debug_print("CBF error: cannot find datablock.\n"));
		while (CBF_SUCCESS==error) {
			/* get some useful parameters out of the metadata as it's converted */
			double pixel_x = 0./0., pixel_y = 0./0.;

			/* then search for the 'array_data' category */
			cbf_onfailnez(cbf_find_category(handle,"array_data"),
                          cbf_debug_print("CBF error: cannot find category 'array_data'.\n"));

			/* First: extract the metadata from the CBF, put it in nexus */
			cbf_failnez(cbf_find_column(handle,"header_convention"));
			if (1) { /* get the header convention, check it is a value I understand */
				const char * value = NULL;
				const char vendor_pilatus[] = "PILATUS";
				cbf_failnez(cbf_get_value(handle,&value));
				if (0 == strncmp(value,vendor_pilatus,strlen(vendor_pilatus))) {
					const char version_1_2[] = "1.2";
					value += strlen(vendor_pilatus) + 1;
					if (0 == strncmp(value,version_1_2,strlen(version_1_2))) {
						/* define tokenisation variables, with default buffer sized to almost always be big enough */
						size_t n = 128;
						char * token = malloc(n*sizeof(char));
						int newline = 1;
						/* Numerical values for use after main parsing loop */
						double beam_x = 0./0., beam_y = 0./0.;
						double detector_distance = 0./0.;
						/* Flags to determine what information I actually have */
						/* Other useful values */
						hid_t pilatusDiagnostics = CBF_H5FAIL; /* <- non-nexus group to dump some possibly useful information into */
						/* Get the header data */
                        cbf_debug_print3("%s_%s header found.\n",vendor_pilatus,version_1_2);
						cbf_onfailnez(cbf_find_column(handle,"header_contents"),
                                      cbf_debug_print("'header_contents' not found.\n"));
						/* re-use the 'value' variable, I won't need the old value anymore */
                        cbf_onfailnez(cbf_get_value(handle,&value), cbf_debug_print("'header_contents' inaccessible.\n"));
                        cbf_H5Drequire_flstring(detector,0,"type","pixel array");

						if (0) {
							const char * _value = value;
							do {
								_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &_value);
								if (!token) break;
								newline = !strcmp("\n",token);
								printf("token: %s\n", token);
							} while (1);
						}
                        cbf_debug_print2("header:\n%s\n",value);

						/*
						Do the mapping, iterating over each line of the header.
						The entire header can be parsed using a trivial FSA, so don't bother with anything particularly complex.
						*/
						do {
							int noMatch = 0;
							{ /* Get the first token */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (!token) break;
								if (!strcmp("\n",token)) continue;
							}
							/* check for a time */
							if (isDateTime(token)) {
								int found = CBF_SUCCESS;
								/* Put the time string into the hdf5 file. */
								hid_t type = CBF_H5FAIL;
								hid_t dataset = CBF_H5FAIL;
                                CBF_CALL(cbf_H5Tcreate_string(&type,H5T_VARIABLE));
								found =  cbf_H5Dfind2(h5handle->nxid,&dataset,"start_time",0,0,0,type);
								if (CBF_SUCCESS==found) {
									/* comparison with existing data, to extract earliest time */
									/* time is in YYYY-MM-DDThh:mm:ss.s* format, should be able to use strcmp to order them */
									/* first read the existing timestamp */
									const hid_t currType = H5Dget_type(dataset);
									const char * buf = 0;
									hid_t currMemType = CBF_H5FAIL;
									cbf_H5Tcreate_string(&currMemType,H5T_VARIABLE);
									cbf_H5Dread2(dataset,0,0,0,&buf,currMemType);
									cbf_H5Tfree(currMemType);
									/* then compare them */
									if (strcmp(token,buf) < 0) {
										/* store the oldest timestamp */
                                        CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&token,type));
									}
									free((void*)buf);
									cbf_H5Tfree(currType);
								} else if (CBF_NOTFOUND==found) {
									/* create the dataset & write the data */
                                    CBF_CALL(cbf_H5Dcreate(h5handle->nxid,&dataset,"start_time",0,0,0,0,type));
                                    CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&token,type));
								} else {
									error |= found;
                                    cbf_debug_print2("error: %s\n",cbf_strerror(found));
								}
								cbf_H5Dfree(dataset);
								found =  cbf_H5Dfind2(h5handle->nxid,&dataset,"end_time",0,0,0,type);
								if (CBF_SUCCESS==found) {
									/* comparison with existing data, to extract latest time */
									/* time is in YYYY-MM-DDThh:mm:ss.s* format, should be able to use strcmp to order them */
									/* first read the existing timestamp */
									const hid_t currType = H5Dget_type(dataset);
									const char * buf = 0;
									hid_t currMemType = CBF_H5FAIL;
									cbf_H5Tcreate_string(&currMemType,H5T_VARIABLE);
									cbf_H5Dread2(dataset,0,0,0,&buf,currMemType);
									cbf_H5Tfree(currMemType);
									/* then compare them */
									if (strcmp(token,buf) > 0) {
										/* store the oldest timestamp */
                                        CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&token,type));
									}
									free((void*)buf);
									cbf_H5Tfree(currType);
								} else if (CBF_NOTFOUND==found) {
									/* create the dataset & write the data */
                                    CBF_CALL(cbf_H5Dcreate(h5handle->nxid,&dataset,"end_time",0,0,0,0,type));
                                    CBF_CALL(cbf_H5Dwrite2(dataset,0,0,0,&token,type));
								} else {
									error |= found;
                                    cbf_debug_print2("error: %s\n",cbf_strerror(found));
								}
								cbf_H5Dfree(dataset);
								cbf_H5Tfree(type);
							} else if (!cbf_cistrcmp("Pixel_size",token)) {
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								{ /* Get x pixel size */
									hid_t h5data = CBF_H5FAIL;
									const double num = strtod(token,0);
                                    CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector,&h5data,"x_pixel_size",num,cmp_double,cmp_params));
                                    CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
									if (cbf_cistrcmp(token,"m")) {
										error |= CBF_H5DIFFERENT;
                                        cbf_debug_print("error: expected units of 'm' for 'Pixel_size'");
									} else {
										pixel_x = num;
									}
                                    CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
									cbf_H5Dfree(h5data);
								}
								/* Get next useful token, just skip over useless stuff */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								{ /* Get y pixel size */
									hid_t h5data = CBF_H5FAIL;
									const double num = strtod(token,0);
                                    CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector,&h5data,"y_pixel_size",num,cmp_double,cmp_params));
                                    CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
									if (cbf_cistrcmp(token,"m")) {
										error |= CBF_H5DIFFERENT;
                                        cbf_debug_print2("error: %s\n","expected units of 'm' for 'Pixel_size'");
									} else {
										pixel_y = num;
									}
                                    CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
									cbf_H5Dfree(h5data);
								}
							} else if (!cbf_cistrcmp("Silicon",token)) {
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (!strcmp("sensor",token)) {
                                    CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
									if (!strcmp("thickness",token)) {
                                        CBF_CALL(cbf_H5Drequire_flstring(detector,0,"sensor_material","Silicon"));
                                        CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
										{
											hid_t h5data = CBF_H5FAIL;
											double num = strtod(token,0);
                                            CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector,&h5data,"sensor_thickness",
                                                                                      num,cmp_double,cmp_params));
                                            CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
											if (cbf_cistrcmp(token,"m")) {
												error |= CBF_H5DIFFERENT;
                                                cbf_debug_print("expected units of 'm' for 'Silicon sensor thickness'");
											}
                                            CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
											cbf_H5Dfree(h5data);
										}
									} else noMatch = 1;
								} else noMatch = 1;
							} else if (!cbf_cistrcmp("Detector_distance",token)) {
								/* Get value & units */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								detector_distance = strtod(token,0);
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (!cbf_cistrcmp(token,"m")) {
									hid_t h5data = CBF_H5FAIL;
									const hsize_t max[] = {H5S_UNLIMITED};
									const hsize_t cnk[] = {1};
									const hsize_t off[] = {h5handle->slice};
									const hsize_t cnt[] = {1};
									hsize_t buf[] = {0};
                                    CBF_CALL(cbf_H5Drequire(detector,&h5data,"distance",1,max,cnk,buf,H5T_IEEE_F64LE));
                                    CBF_CALL(cbf_H5Dinsert(h5data,off,0,cnt,buf,&detector_distance,H5T_NATIVE_DOUBLE));
                                    CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
									cbf_H5Dfree(h5data);
								} else {
									error |= CBF_H5DIFFERENT;
                                    cbf_debug_print("error: expected units of 'm' for 'Detector_distance'");
								}
							} else if (!cbf_cistrcmp("Detector",token)) {
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(detector,0,"description",token));
							} else if (!cbf_cistrcmp("N_excluded_pixels",token)) {
								hid_t h5location = CBF_H5FAIL;
                                CBF_CALL(_cbf_NXGrequire(detector,&h5location,"pilatus_diagnostics","NXcollection"));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(h5location,0,"N_excluded_pixels",token));
								cbf_H5Gfree(h5location);
							} else if (!cbf_cistrcmp("Excluded_pixels",token)) {
								hid_t h5location = CBF_H5FAIL;
                                CBF_CALL(_cbf_NXGrequire(detector,&h5location,"pilatus_diagnostics","NXcollection"));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(h5location,0,"Excluded_pixels",token));
								cbf_H5Gfree(h5location);
							} else if (!cbf_cistrcmp("Flat_field",token)) {
								hid_t h5location = CBF_H5FAIL;
                                CBF_CALL(_cbf_NXGrequire(detector,&h5location,"pilatus_diagnostics","NXcollection"));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(h5location,0,"Flat_field",token));
								cbf_H5Gfree(h5location);
							} else if (!cbf_cistrcmp("Trim_file",token)) {
								hid_t h5location = CBF_H5FAIL;
                                CBF_CALL(_cbf_NXGrequire(detector,&h5location,"pilatus_diagnostics","NXcollection"));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(h5location,0,"Trim_file",token));
								cbf_H5Gfree(h5location);
							} else if (!cbf_cistrcmp("Exposure_time",token)) {
								hid_t h5data = CBF_H5FAIL;
								hid_t h5location = detector;
								const hid_t h5type = H5T_IEEE_F64LE;
								const char h5name[] = "count_time";
								const hsize_t max[] = {H5S_UNLIMITED};
								const hsize_t chunk[] = {1};
								const hsize_t offset[] = {h5handle->slice};
								const hsize_t count[] = {1};
								hsize_t buf[] = {0};
								double num = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,0);
                                CBF_CALL(cbf_H5Drequire(h5location,&h5data,h5name,1,max,chunk,buf,h5type));
                                CBF_CALL(cbf_H5Dinsert(h5data,offset,0,count,buf,&num,H5T_NATIVE_DOUBLE));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
								cbf_H5Dfree(h5data);
							} else if (!cbf_cistrcmp("Exposure_period",token)) {
								hid_t h5data = CBF_H5FAIL;
								hid_t h5location = detector;
								const hid_t h5type = H5T_IEEE_F64LE;
								const char h5name[] = "frame_time";
								const hsize_t max[] = {H5S_UNLIMITED};
								const hsize_t chunk[] = {1};
								const hsize_t offset[] = {h5handle->slice};
								const hsize_t count[] = {1};
								hsize_t buf[] = {0};
								double num = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,0);
                                CBF_CALL(cbf_H5Drequire(h5location,&h5data,h5name,1,max,chunk,buf,h5type));
                                CBF_CALL(cbf_H5Dinsert(h5data,offset,0,count,buf,&num,H5T_NATIVE_DOUBLE));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
								cbf_H5Dfree(h5data);
							} else if (!cbf_cistrcmp("Tau",token)) {
								hid_t h5data = CBF_H5FAIL;
								hid_t h5location = detector;
								const char h5name[] = "dead_time";
								double num = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,0);
                                CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(h5location,&h5data,h5name,num,cmp_double,cmp_params));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
								cbf_H5Dfree(h5data);
							} else if (!cbf_cistrcmp("Count_cutoff",token)) {
								/* store the string for later interpretation */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (CBF_SUCCESS==error) {
									saturation_value = _cbf_strdup(token);
								}
							} else if (!cbf_cistrcmp("Threshold_setting",token)) {
								double num = 0./0.;
								hid_t h5data = CBF_H5FAIL;
								/* Get value & units */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,0);
                                CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector,&h5data,"threshold_energy", num,cmp_double,cmp_params));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
								cbf_H5Dfree(h5data);
							} else if (!cbf_cistrcmp("Gain_setting",token)) {
								int error = CBF_SUCCESS;
								/* [1,end): gain setting string */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 1, &value));
                                CBF_CALL(cbf_H5Drequire_flstring(detector,0,"gain_setting",token));
							} else if (!cbf_cistrcmp("Wavelength",token)) {
								/* Get value & units */
								hid_t h5data = CBF_H5FAIL;
                                hid_t sample = CBF_H5FAIL;
                                hid_t beam = CBF_H5FAIL;
								const hid_t h5type = H5T_IEEE_F64LE;
								const char h5name[] = "incident_wavelength";
								const hsize_t max[] = {H5S_UNLIMITED};
								const hsize_t chunk[] = {1};
								const hsize_t offset[] = {h5handle->slice};
								const hsize_t count[] = {1};
								hsize_t buf[] = {0};
								double num = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,0);
                                CBF_CALL(cbf_h5handle_require_sample(h5handle, &sample,0));
                                CBF_CALL(_cbf_NXGrequire(sample,&beam,"beam","NXbeam"));
                                CBF_CALL(cbf_H5Drequire(beam,&h5data,h5name,1,max,chunk,buf,h5type));
                                CBF_CALL(cbf_H5Dinsert(h5data,offset,0,count,buf,&num,H5T_NATIVE_DOUBLE));
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (!strcmp(token,"A")||!strcmp(token,"angstroms")) {
									CBF_CALL(cbf_H5Arequire_string(h5data,"units","angstroms"));
								} else {
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units",token));
								}
                                cbf_H5Gfree(beam);
								cbf_H5Dfree(h5data);
							} else if (!cbf_cistrcmp("Beam_xy",token)) {
								/*
								Extract x & y positions from the header, put them into the file later.
								I might need to read all the header to know if I can actually convert these values to NeXus data.
								*/
								double num_x = 0./0., num_y = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num_x = strtod(token,0);
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num_y = strtod(token,0);
								/* Extract the units (should be pixels, but I don't want to lose important information if it isn't) */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (cbf_cistrcmp(token,"pixels")) {
									error |= CBF_H5DIFFERENT;
                                    cbf_debug_print("error: expected units of 'pixels' for 'Beam_xy'");
								} else {
									beam_x = num_x;
									beam_y = num_y;
								}
							} else if (!cbf_cistrcmp("Flux",token)) {
								/*
								Either a number with some units or a random string, only do anything if it's a number.
								*/
								const char * end = 0;
								double num = 0./0.;
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								num = strtod(token,(char**)(&end));
								if (end != token && 0.0 != num) {
									/* I have a valid & useful flux, map it to /entry/sample/beam/flux */
									hid_t sample = CBF_H5FAIL; /* DO NOT FREE THIS! */
									hid_t h5data = CBF_H5FAIL;
									hid_t h5location = CBF_H5FAIL;
									/* Ensure I have a valid sample group */
                                    CBF_CALL(cbf_h5handle_require_sample(h5handle, &sample,0));
									/* Ensure I have a valid beam group */
                                    CBF_CALL(cbf_H5Grequire(sample,&h5location,"beam"));
                                    CBF_CALL(cbf_H5Arequire_string(h5location, "NX_class", "NXbeam"));
									/* Store value & units */
                                    CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(h5location, &h5data, "flux", num, cmp_double,cmp_params));
                                    CBF_CALL(cbf_H5Arequire_string(h5data, "units", "s-1"));
									/* cleanup temporary dataset */
									cbf_H5Dfree(h5data);
									cbf_H5Gfree(h5location);
								}
							} else if (!cbf_cistrcmp("Filter_transmission",token)) {
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								/* write it to the file */
								if (cbf_H5Ivalid(instrument)) {
									/* Get value */
									const double num = strtod(token,0);
									hid_t h5location = CBF_H5FAIL;
                                    CBF_CALL(cbf_H5Grequire(instrument,&h5location,"attenuator"));
                                    CBF_CALL(cbf_H5Arequire_string(h5location, "NX_class", "NXattenuator"));
									/* Get value & units */
                                    CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(h5location, 0, "attenuator_transmission",
                                                                              num, cmp_double,cmp_params));
									/* cleanup temporary dataset */
									cbf_H5Gfree(h5location);
								}
							} else if (!cbf_cistrcmp("Polarization",token)) {
								hid_t sample = CBF_H5FAIL; /* DO NOT FREE THIS! */
								hid_t h5location = CBF_H5FAIL;
								/* Ensure I have a valid sample group */
                                CBF_CALL(cbf_h5handle_require_sample(h5handle, &sample,0));
								/* Ensure I have a valid beam group */
                                CBF_CALL(cbf_H5Grequire(sample,&h5location,"beam"));
                                CBF_CALL(cbf_H5Arequire_string(h5location, "NX_class", "NXbeam"));
								/* Get value & units */
                                CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value));
								if (CBF_SUCCESS==error) {
									/* extract value from header */
									const double p = strtod(token, 0);
									/* convert to nexus format */
									const double polarisation[] = {1.0, p, 0.0, 0.0};
									const hsize_t max[] = {H5S_UNLIMITED,4};
									const hsize_t chunk[] = {1,4};
									const hsize_t offset[] = {h5handle->slice,0};
									const hsize_t count[] = {1,4};
									hsize_t buf[] = {0,0};
									hid_t h5data = CBF_H5FAIL;
									hid_t h5type = H5T_IEEE_F64LE;
									const char h5name[] = "incident_polarisation_stokes";
                                    CBF_CALL(cbf_H5Drequire(h5location,&h5data,h5name,2,max,chunk,buf,h5type));
                                    CBF_CALL(cbf_H5Dinsert(h5data,offset,0,count,buf,polarisation,H5T_NATIVE_DOUBLE));
									cbf_H5Dfree(h5data);
								}
								cbf_H5Gfree(h5location);
							} else if (!cbf_cistrcmp("Alpha",token)) {
#define _CBF_CONVERT_AXIS(axisName) \
CBFM_PROLOG { \
	/* Find the data for the current axis, or fail */ \
	cbf_configItem_t * const axisItem = cbf_config_findMinicbf(axisConfig, axisName); \
CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value)); \
	if (cbf_config_end(axisConfig) == axisItem) { \
		error |= CBF_NOTFOUND; \
cbf_debug_print2("Config settings for axis '%s' could not be found: " \
				"this will eventually be a fatal error\n", axisName); \
							} else if (axisItem->convert) { \
		hid_t h5data = CBF_H5FAIL; \
		hid_t sample = CBF_H5FAIL; \
		hid_t axes = CBF_H5FAIL; \
		const hsize_t max[] = {H5S_UNLIMITED}; \
		const hsize_t chunk[] = {1}; \
		const hsize_t offset[] = {h5handle->slice}; \
		const hsize_t count[] = {1}; \
		hsize_t buf[] = {0}; \
		const double num = strtod(token,0); \
CBF_CALL(cbf_h5handle_require_sample(h5handle, &sample,0)); \
CBF_CALL(cbf_H5Grequire(sample,&axes,"transformations")); \
CBF_CALL(cbf_H5Arequire_string(axes,"NX_class","NXtransformations")); \
CBF_CALL(cbf_H5Drequire(axes,&h5data,axisItem->nexus,1,max,chunk,buf,H5T_IEEE_F64LE)); \
CBF_CALL(cbf_H5Dinsert(h5data,offset,0,count,buf,&num,H5T_NATIVE_DOUBLE)); \
CBF_CALL(_cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value)); \
		if (axisItem->depends_on) { \
			const char dot[] = "."; \
			if (strcmp(axisItem->depends_on,dot)) { \
				const char path_empty[] = ""; \
				const char path_sample[] = "sample"; \
const char axis_group_name[] = "transformations"; \
				const char * path_parts[] = { \
					path_empty, \
					h5handle->nxid_name, \
					path_sample, \
					axis_group_name, \
					axisItem->depends_on, \
					0 \
							}; \
				const char * const axis_path = _cbf_strjoin(path_parts,'/'); \
CBF_CALL(CBFM_pilatusAxis2nexusAxisAttrs(h5data,token,axis_path,axisItem,cmp_double,cmp_params )); \
				free((void*)axis_path); \
							} else { \
CBF_CALL(CBFM_pilatusAxis2nexusAxisAttrs(h5data,token,dot,axisItem,cmp_double,cmp_params)); \
							} \
							} else { \
CBF_CALL(CBFM_pilatusAxis2nexusAxisAttrs(h5data,token,"",axisItem,cmp_double,cmp_params)); \
							} \
		cbf_H5Dfree(h5data); \
		cbf_H5Gfree(axes); \
							} \
} CBFM_EPILOG
								_CBF_CONVERT_AXIS("Alpha");
							} else if (!cbf_cistrcmp("Kappa",token)) {
								_CBF_CONVERT_AXIS("Kappa");
							} else if (!cbf_cistrcmp("Phi",token)) {
								_CBF_CONVERT_AXIS("Phi");
							} else if (!cbf_cistrcmp("Chi",token)) {
								_CBF_CONVERT_AXIS("Chi");
							} else if (!cbf_cistrcmp("Omega",token)) {
								_CBF_CONVERT_AXIS("Omega");
							} else if (!cbf_cistrcmp("Start_angle",token)) {
								_CBF_CONVERT_AXIS("Start_angle");
							} else if (!cbf_cistrcmp("Detector_2theta",token)) {
								_CBF_CONVERT_AXIS("Detector_2theta");
							} else if (!cbf_cistrcmp("Image_path",token)) {
							} else if (!cbf_cistrcmp("Angle_increment",token)) {
							} else noMatch = 1;
							if (noMatch) {
                                cbf_debug_print2("warning: Could not match entry in pilatus header: '%s'\n",token);
							}
							/* Done matching the entry from this line, go on to the next one */
							while (token && strcmp("\n",token)) {
								error = _cbf_scan_pilatus_V1_2_miniheader(&token, &n, &newline, 0, &value);
                                if (error) cbf_debug_print2("error %s\n",cbf_strerror(error));
							}
						} while (1);
						free(token);

						{
							/*
							Record the axis that the sample depends on
							*/
                            const char * const depends_on = cbf_config_getSampleDependsOn(axisConfig);
							if (depends_on) {
								hid_t h5location = CBF_H5FAIL; /* DO NOT FREE THIS */
								const char path_empty[] = "";
								const char path_sample[] = "sample";
                                const char axis_group_name[] = "transformations";
								const char * path_parts[] = {
									path_empty,
									h5handle->nxid_name,
									path_sample,
									axis_group_name,
									depends_on,
									0
								};
								const char * const axis_path = _cbf_strjoin(path_parts,'/');
                                CBF_CALL(cbf_h5handle_require_sample(h5handle, &h5location,0));
                                CBF_CALL(cbf_H5Drequire_flstring(h5location,0,"depends_on",axis_path));
								free((void*)axis_path);
							} else {
                                cbf_debug_print("Config settings for 'Sample' could not be found: "
										"this will eventually be a fatal error\n");
							}
                            cbf_debug_print("'sample/depends_on' written\n");
						}
						{ /* write beam_center_x */
							hid_t h5data = CBF_H5FAIL;
                            CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector, &h5data, "beam_center_x",
                                                                      beam_x*pixel_x, cmp_double, cmp_params));
                            CBF_CALL(cbf_H5Arequire_string(h5data,"units","m"));
							cbf_H5Dfree(h5data);
						}
						{ /* write beam_center_y */
							hid_t h5data = CBF_H5FAIL;
                            CBF_CALL(CBFM_H5Drequire_scalar_F64LE2(detector, &h5data, "beam_center_y",
                                                                      beam_y*pixel_y, cmp_double, cmp_params));
                            CBF_CALL(cbf_H5Arequire_string(h5data,"units","m"));
							cbf_H5Dfree(h5data);
						}
						{
							/* Detector axes
							Requires:
							* beam_center_x
							* beam_center_y
							* detector_distance
                             Creates dependency chain:
							detector -> rotation -> translation -> .
							*/
							/* TODO: write depends_on attributes with full paths */
							/* Common settings */
							const hsize_t vdims[] = {3};
                            double vbuf[3] = {0./0.};
							const hsize_t max[] = {H5S_UNLIMITED};
							hsize_t buf[] = {0};
							const hsize_t chunk[] = {1};
							const hsize_t h5offset[] = {h5handle->slice};
							const hsize_t h5count[] = {1};
							hid_t h5location = detector;
							hid_t axis_group = CBF_H5FAIL;
							const char * axis_translation = "translation";
							const char * axis_rotation = "rotation";
							const char path_empty[] = "";
                            const char axis_group_name[] = "transformations";
                            CBF_CALL(cbf_H5Grequire(h5location,&axis_group,axis_group_name));
                            CBF_CALL(cbf_H5Arequire_string(axis_group,"NX_class","NXtransformations"));
							{ /* Translation-specific */
								hid_t h5data = CBF_H5FAIL;
								hid_t h5type = H5T_IEEE_F64LE;
								const double num = detector_distance;
								const double vector[] = {0.0, 0.0, 1.0};
								const double offset[] = {-beam_x*pixel_x, -beam_y*pixel_y, 0.0};
                                CBF_CALL(cbf_H5Drequire(axis_group,&h5data,axis_translation,1,max,chunk,buf,h5type));
                                CBF_CALL(cbf_H5Dinsert(h5data,h5offset,0,h5count,buf,&num,H5T_NATIVE_DOUBLE));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units","m"));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"offset_units","m"));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"transformation_type","translation"));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"depends_on","."));
                                CBF_CALL(CBFM_H5Arequire_cmp2(h5data,"vector",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,vector,
                                                                 vbuf,cmp_double,cmp_params));
                                CBF_CALL(CBFM_H5Arequire_cmp2(h5data,"offset",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,offset,
                                                                 vbuf,cmp_double,cmp_params));
								/* cleanup temporary datasets */
								cbf_H5Dfree(h5data);
                                cbf_debug_print2("'detector/%s' written\n",axis_translation);
							}
							{ /* Rotation-specific */
								hid_t h5data = CBF_H5FAIL;
								hid_t h5type = H5T_IEEE_F64LE;
								const double num = 180.0;
								const double vector[] = {0.0, 0.0, 1.0};
								const char * path_parts[] = {
									path_empty,
									h5handle->nxid_name,
									h5handle->nxinstrument_name,
									h5handle->nxdetector_names[h5handle->cur_detector],
									axis_group_name,
									axis_translation,
									0
								};
								const char * const axis_path = _cbf_strjoin(path_parts,'/');
                                CBF_CALL(cbf_H5Drequire(axis_group,&h5data,axis_rotation,1,max,chunk,buf,h5type));
                                CBF_CALL(cbf_H5Dinsert(h5data,h5offset,0,h5count,buf,&num,H5T_NATIVE_DOUBLE));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"units","degrees"));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"transformation_type","rotation"));
                                CBF_CALL(cbf_H5Arequire_string(h5data,"depends_on",axis_path));
                                CBF_CALL(CBFM_H5Arequire_cmp2(h5data,"vector",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,
                                                                 vector, vbuf,cmp_double,cmp_params));
								/* cleanup temporary datasets */
								cbf_H5Dfree(h5data);
								free((void*)axis_path);
                                cbf_debug_print2("'detector/%s' written\n",axis_rotation);
							}
							cbf_H5Gfree(axis_group);
							{ /* tie everything to the detector */
								const char * path_parts[] = {
									path_empty,
									h5handle->nxid_name,
									h5handle->nxinstrument_name,
									h5handle->nxdetector_names[h5handle->cur_detector],
									axis_group_name,
									axis_rotation,
									0
								};
								const char * const axis_path = _cbf_strjoin(path_parts,'/');
                                CBF_CALL(cbf_H5Drequire_flstring(detector,0,"depends_on",axis_path));
								free((void*)axis_path);
							}
						}
						cbf_H5Gfree(pilatusDiagnostics);
					}
				}
			}
			/* Second: extract the raw data from the CBF, put it in nexus */
            cbf_onfailnez(cbf_find_column(handle,"data"), cbf_debug_print("error: cannot find column `data'.\n"));
			/* get the first row, TODO: convert every row */
            cbf_onfailnez(cbf_select_row(handle,0), cbf_debug_print("error: cannot find row 0.\n"));
			if(1) {
				hsize_t h5dim[] = {0, 0, 0};
				/* convert the data */
                CBF_CALL(cbf_write_array_h5file(handle->node, handle->row, h5handle, saturation_value, 0, h5dim));
				/* ensure I have an axis for each index of the image - mapping pixel indices to spatial coordinates */
				if (1) {
					hid_t h5axis = CBF_H5FAIL;
                    const char h5name[] = "x_pixel_offset";
					hsize_t buf[] = {0};
                    const int found =  cbf_H5Dfind2(detector,&h5axis,h5name,1,h5dim+2,buf,H5T_IEEE_F64LE);
					const hsize_t offset[] = {0};
                    const hsize_t * count = h5dim+2;
					double * const expected_data = malloc((*count) * sizeof(double));
					{
						hsize_t n = 0;
                        for (n=0; n!=h5dim[2]; ++n)
							expected_data[n] = (double)(n)*pixel_x;
					}
					if (CBF_SUCCESS==found) {
						double * const actual_data = malloc((*count) * sizeof(double));
                        CBF_CALL(cbf_H5Dread2(h5axis,offset,0,count,actual_data,H5T_NATIVE_DOUBLE));
                        if (CBFM_cmp_double(expected_data, actual_data, *count, cmp_params)) {
                            cbf_debug_print2("error: data doesn't match in %s, x pixel size might not match\n",h5name);
							error |= CBF_H5DIFFERENT;
						}
						free((void*)(actual_data));
					} else if (CBF_NOTFOUND==found) {
                        CBF_CALL(cbf_H5Dcreate(detector,&h5axis,h5name,1,h5dim+2,h5dim+2,0,H5T_IEEE_F64LE));
                        CBF_CALL(cbf_H5Dwrite2(h5axis,offset,0,count,expected_data,H5T_NATIVE_DOUBLE));
					} else {
						error |= found;
                        cbf_debug_print2("Error locating axis: %s\n",cbf_strerror(found));
					}
					free((void*)(expected_data));
                    CBF_CALL(cbf_H5Arequire_string(h5axis,"units","m"));
					{
						const double vector[] = {1.0, 0.0, 0.0};
						const hsize_t vdims[] = {3};
						double vbuf[3] = {0./0.};
                        CBF_CALL(CBFM_H5Arequire_cmp2(h5axis,"vector",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,
                                                         vector,vbuf,cmp_double,cmp_params));
					}
                    CBF_CALL(cbf_H5Arequire_string(h5axis,"transformation_type","translation"));
					{
						const char path_empty[] = "";
                        const char path_transformations[] = "transformations";
						const char path_axis[] = "rotation";
						const char * const path_parts[] = {
							path_empty,
							h5handle->nxid_name,
                            h5handle->nxinstrument_name,
							h5handle->nxdetector_names[h5handle->cur_detector],
                            path_transformations,
							path_axis,
							0
						};
						const char * axis_path = _cbf_strjoin(path_parts,'/');
                        CBF_CALL(cbf_H5Arequire_string(h5axis,"depends_on",axis_path));
						free((void*)axis_path);
					}
					cbf_H5Dfree(h5axis);
				}
				if (1) {
					hid_t h5axis = CBF_H5FAIL;
                    const char h5name[] = "y_pixel_offset";
					hsize_t buf[] = {0};
                    const int found =  cbf_H5Dfind2(detector,&h5axis,h5name,1,h5dim+1,buf,H5T_IEEE_F64LE);
					const hsize_t offset[] = {0};
                    const hsize_t * count = h5dim+1;
					double * const expected_data = malloc((*count) * sizeof(double));
					{
						hsize_t n = 0;
                        for (n=0; n!=h5dim[1]; ++n)
							expected_data[n] = (double)(n)*pixel_y;
					}
					if (CBF_SUCCESS==found) {
						double * const actual_data = malloc((*count) * sizeof(double));
                        CBF_CALL(cbf_H5Dread2(h5axis,offset,0,count,actual_data,H5T_NATIVE_DOUBLE));
                        if (CBFM_cmp_double(expected_data, actual_data, *count, cmp_params)) {
                            cbf_debug_print2("error: data doesn't match in %s, y pixel size might not match\n",h5name);
							error |= CBF_H5DIFFERENT;
						}
						free((void*)(actual_data));
					} else if (CBF_NOTFOUND==found) {
                        CBF_CALL(cbf_H5Dcreate(detector,&h5axis,h5name,1,h5dim+1,h5dim+1,0,H5T_IEEE_F64LE));
                        CBF_CALL(cbf_H5Dwrite2(h5axis,offset,0,count,expected_data,H5T_NATIVE_DOUBLE));
					} else {
						error |= found;
                        cbf_debug_print2("Error locating axis: %s\n",cbf_strerror(found));
					}
					free((void*)(expected_data));
                    CBF_CALL(cbf_H5Arequire_string(h5axis,"units","m"));
					{
						const double vector[] = {0.0, 1.0, 0.0};
						const hsize_t vdims[] = {3};
						double vbuf[3] = {0./0.};
                        CBF_CALL(CBFM_H5Arequire_cmp2(h5axis,"vector",1,vdims,H5T_IEEE_F64LE,H5T_NATIVE_DOUBLE,
                                                         vector,vbuf,cmp_double,cmp_params));
					}
                    CBF_CALL(cbf_H5Arequire_string(h5axis,"transformation_type","translation"));
					{
						const char path_empty[] = "";
                        const char path_transformations[] = "transformations";
						const char path_axis[] = "rotation";
						const char * const path_parts[] = {
							path_empty,
							h5handle->nxid_name,
                            h5handle->nxinstrument_name,
							h5handle->nxdetector_names[h5handle->cur_detector],
                            path_transformations,
							path_axis,
							0
						};
						const char * axis_path = _cbf_strjoin(path_parts,'/');
                        CBF_CALL(cbf_H5Arequire_string(h5axis,"depends_on",axis_path));
						free((void*)axis_path);
					}
					cbf_H5Dfree(h5axis);
				}
                CBF_CALL(cbf_write_cbf2nx__link_h5data(handle, h5handle));
			}
			free((void*)saturation_value);
			++h5handle->slice;
			if (CBF_SUCCESS != cbf_next_datablock(handle)) break;
		}

		return error;
	}


    /* Open an HDF5 File handle */

    int cbf_open_h5handle(cbf_h5handle *h5handle,
                          const char * h5filename) {

        hid_t fcreate_prop_list;

        /* check that the file name has been specified and
         is an HDF5 file */

        if (!h5filename || !H5Fis_hdf5(h5filename)) return CBF_ARGUMENT;

        /* ensure the HDF5 library is ready */

        cbf_h5failneg(H5open(),CBF_ARGUMENT);

        cbf_failnez(cbf_make_h5handle(h5handle));

        cbf_h5onfailneg(fcreate_prop_list = H5Pcreate(H5P_FILE_ACCESS),
                        CBF_ALLOC,cbf_free((void**) h5handle, NULL));

        (*h5handle)->rwmode = 0;

        cbf_h5onfailneg(H5Pset_fclose_degree(fcreate_prop_list,H5F_CLOSE_STRONG),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        cbf_h5onfailneg((*h5handle)->hfile = H5Fopen(h5filename,
                                                     H5F_ACC_RDONLY,fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        cbf_h5onfailneg(H5Pclose(fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));

        return CBF_SUCCESS;

    }

    /* Convert an HDF5 typeclass to a string
     and flag for atomic or not
     copies up to n-1 characters of the
     type string to buffer*/

    int cbf_h5type_class_string(H5T_class_t type_class,
                                char * buffer,
                                int * atomic, size_t n ) {

        int good_type;

        good_type = 0;

        *atomic = 1;

        buffer[n-1] = '\0';

        switch(type_class) {
            case H5T_INTEGER:
                strncpy(buffer,"H5T_INTEGER",n-1);
                break;
            case H5T_FLOAT:
                strncpy(buffer,"H5T_FLOAT",n-1);
                break;
            case H5T_STRING:
                strncpy(buffer,"H5T_STRING",n-1);
                break;
            case H5T_BITFIELD:
                strncpy(buffer,"H5T_BITFIELD",n-1);
                break;
            case H5T_OPAQUE:
                strncpy(buffer,"H5T_OPAQUE",n-1);
                break;
            case H5T_COMPOUND:
                strncpy(buffer,"H5T_COMPOUND",n-1);
                *atomic = 0;
                break;
            case H5T_REFERENCE:
                strncpy(buffer,"H5T_REFERENCE",n-1);
                break;
            case H5T_ENUM:
                strncpy(buffer,"H5T_ENUM",n-1);
                *atomic = 0;
                break;
            case H5T_VLEN:
                strncpy(buffer,"H5T_VLEN",n-1);
                *atomic = 0;
                break;
            case H5T_ARRAY:
                strncpy(buffer,"H5T_ARRAY",n-1);
                *atomic = 0;
                break;
            case -1:
                strncpy(buffer,".",n-1);
                good_type = CBF_ARGUMENT;
                *atomic = 0;
                break;
            default:
                strncpy(buffer,"UNKNOWN",n-1);
                good_type = CBF_ARGUMENT;
                *atomic = 0;
                break;
        }

        return good_type;

    }

    /* Store an HDF5 Dataset in CBF handle, using
     category categoryname, ...*/

    int cbf_h5ds_store(cbf_handle handle, haddr_t parent,
                       const char * parent_name,
                       const int target_row,
                       const char * categoryname, hid_t obj_id,
                       hid_t space, hid_t type,
                       const char * name,
                       const int readattrib,
                       void ** value) {

        char buffer[25];

        int errorcode;

        unsigned char* data;

        char h5t_type_class[14], h5t_base_type_class[14];

        hid_t base_type;

        hid_t native_type;

        int atomic;

        int ndims, kdims, ii;

        unsigned int rows;

        hsize_t dims[H5S_MAX_RANK];

        hsize_t maxdims[H5S_MAX_RANK];

        char * byte_order;

        size_t type_size, total_size, total_dim;

        H5T_class_t type_class, base_type_class;

        H5T_order_t type_order;

        H5T_sign_t type_sign = H5T_SGN_ERROR;

        errorcode = 0;

        cbf_reportnez(cbf_require_category(handle,categoryname),errorcode);

        /*  Give the name of this dataset as its own id */

        cbf_reportnez(cbf_require_column(handle,"id"),errorcode);

        cbf_reportnez(cbf_count_rows(handle,&rows),errorcode);

        if (target_row==-1) {

            cbf_reportnez(cbf_new_row(handle),errorcode);

        } else {

            if ((unsigned int)target_row >= rows ) {

                for (ii=rows; ii <= target_row; ii++) {

                    cbf_reportnez(cbf_new_row(handle),errorcode);

                }
            }

            cbf_reportnez(cbf_select_row(handle,target_row),errorcode);
        }

        cbf_reportnez(cbf_set_value(handle,name),errorcode);

        /*  Give the parent name and id for this dataset */

        cbf_reportnez(cbf_require_column(handle,"parent_name"),errorcode);

        cbf_reportnez(cbf_set_value(handle,parent_name),errorcode);

        cbf_reportnez(cbf_require_column(handle,"parent_id"),errorcode);

        sprintf(buffer,"0x%lx",(unsigned long)parent);

        cbf_reportnez(cbf_set_value(handle,buffer),errorcode);


        /* get the class, and, if not atomic
         try to get the base class for an array
         give up otherwise */

        type_class = H5Tget_class(type);

        native_type = H5Tget_native_type(type,H5T_DIR_ASCEND);

        base_type = CBF_H5FAIL;

        cbf_reportnez(cbf_require_column(handle,"type"),errorcode);

        type_size = 0;

        if (value) *value = 0;

        type_order = -1;

        kdims= ndims = H5Sget_simple_extent_ndims(space);

        if (ndims <= 0) ndims = 1;

        H5Sget_simple_extent_dims(space,dims,maxdims);

        if (!cbf_h5type_class_string(
                                     type_class,
                                     h5t_type_class,&atomic,14)) {

            cbf_reportnez(cbf_set_value(handle, h5t_type_class),errorcode);

            if (!atomic && type_class==H5T_ARRAY){
                base_type = H5Tget_super(type);

                base_type_class = H5Tget_class(base_type);

                if (!cbf_h5type_class_string(
                                             base_type_class,
                                             h5t_base_type_class,&atomic,14)) {
                    if (!atomic) {
                        strncpy (h5t_base_type_class,".",14);
                        cbf_h5failneg(H5Tclose(base_type),CBF_FORMAT);
                        base_type = CBF_H5FAIL;
                    } else {

                        type_size = H5Tget_size(base_type);

                        type_order = H5Tget_order(base_type);

                        type_sign = H5Tget_sign(base_type);

                        cbf_reportnez(cbf_require_column(handle,"base_type"),errorcode);

                        cbf_reportnez(cbf_set_value(handle,h5t_base_type_class),errorcode);
                    }
                } else {
                    strncpy (h5t_base_type_class,".",14);
                    cbf_h5failneg(H5Tclose(base_type),CBF_FORMAT);
                    base_type = CBF_H5FAIL;
                }

            } else if (atomic) {

                type_size = H5Tget_size(native_type);

                type_order = H5Tget_order(type);

                type_sign = H5Tget_sign(type);

            }

        }

        total_size = type_size;

        total_dim = 1;

        for (ii=0; ii < kdims; ii ++) {

            total_size *= dims[ii];

            total_dim *= dims[ii];

        }


        if (total_size < type_size) total_size = type_size;

        if (total_dim < 1 ) total_dim = 1;

        cbf_reportnez(cbf_require_column(handle,"value"),errorcode);

        if(total_size > 0) {

            if(readattrib) {

                /* Process an attribute */

                cbf_reportnez(cbf_alloc(((void **) value),NULL,
                                        1,total_size+1),errorcode);

                cbf_h5failneg(H5Aread(obj_id,native_type,(void *)*value),
                              CBF_ARGUMENT);

                (*((char **)value))[total_size]='\0';

                if (type_class==H5T_STRING) {

                    cbf_reportnez(cbf_set_value(handle,(const char *)(*value)),errorcode);

                } else if (type_class==H5T_INTEGER){

                    /* Read of a single integer or an integer array of
                     up to 3 dimensions */

                    char * ivalue;

                    long xdata = 0;

                    unsigned long uxdata = 0;

                    int sign;

                    sign = (type_sign==H5T_SGN_2)?1:0;

                    if (total_dim ==1) {

                        cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                1,type_size*3+1),errorcode);

                        if (H5Tequal(native_type,H5T_NATIVE_CHAR)&&sign) xdata = **((signed char **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_CHAR)&&!sign) uxdata = **((unsigned char **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_SCHAR)) xdata = **((signed char **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_UCHAR)) uxdata = **((unsigned char **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_SHORT)) xdata = **((unsigned short **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_USHORT)) uxdata = **((unsigned short **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_INT)) xdata = **((int **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_UINT)) uxdata = **((unsigned int **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_LONG)) xdata = **((long **)value);
                        if (H5Tequal(native_type,H5T_NATIVE_ULONG)) uxdata = **((unsigned long **)value);

                        if (sign) {

                            sprintf(ivalue,"%ld",xdata);

                        } else {

                            sprintf(ivalue,"%lu",uxdata);

                        }

                        cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                        cbf_reportnez(cbf_free((void**)value,NULL),errorcode);

                        *value = (unsigned char *)ivalue;

                    } else {



                        /* process arrays of up to 100 as
                         bracketed strings
                         */

                        if (total_dim < 101) {

                            size_t indices[H5S_MAX_RANK];

                            size_t master_index, ival_index;

                            int idim, level;

                            char buffer[40];

                            cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                    1,total_dim*((type_size*3)+kdims*2)+1),errorcode);

                            for (idim = 0; idim < kdims; idim ++) {

                                indices[idim] = 0;

                                ivalue[idim] = '[';

                            }

                            level = kdims-1;

                            ival_index = kdims;

                            master_index = 0;

                            while (master_index < total_dim) {

                                for (indices[level]=0; indices[level] < dims[level];) {

                                    if (H5Tequal(native_type,H5T_NATIVE_CHAR)&&sign) xdata = ((*(signed char **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_CHAR)&&!sign) uxdata = ((*(unsigned char **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_SCHAR)) xdata = ((*(signed char **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_UCHAR)) uxdata = ((*(unsigned char **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_SHORT)) xdata = ((*(unsigned short **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_USHORT)) uxdata = ((*(unsigned short **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_INT)) xdata = ((*(int **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_UINT)) uxdata = ((*(unsigned int **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_LONG)) xdata = ((*(long **)value)[master_index]);
                                    if (H5Tequal(native_type,H5T_NATIVE_ULONG)) uxdata = ((*(unsigned long **)value)[master_index]);


                                    if (sign) {

                                        sprintf(buffer,"%ld",xdata);

                                    } else {

                                        sprintf(buffer,"%lu",uxdata);

                                    }

                                    strcat(ivalue+ival_index,buffer);

                                    ival_index+=strlen(buffer);

                                    ivalue[ival_index++]= (indices[level] < dims[level]-1)?',':']';

                                    master_index++;

                                    indices[level]++;

                                    if (indices[level] == dims[level]) {

                                        /* We are at the end of a fast-dimension row
                                         and therefore need to update higher level indices
                                         if any.  */

                                        indices[level] = 0;

                                        level --;

                                        while (level >= 0) {

                                            indices[level]++;

                                            if (indices[level] < dims[level]) {

                                                ivalue[ival_index++] = ',';

                                                ivalue[ival_index++] = '[';

                                                level++;

                                                break;

                                            } else {

                                                ivalue[ival_index++] = ']';

                                                indices[level] = 0;

                                                level --;

                                            }

                                        }

                                        if (level < 0) break;

                                        while (level > kdims-1) {

                                            ivalue[ival_index++] = '[';

                                            level++;

                                        }

                                    }

                                }

                            }

                            ivalue[ival_index++] = '\0';

                            cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                            cbf_reportnez(cbf_set_typeofvalue(handle,"bkts"),errorcode);

                            cbf_reportnez(cbf_free((void**)value,NULL),errorcode);

                            *value = (unsigned char *)ivalue;

                        } else {

                            size_t dimfast, dimmid, dimslow;

                            dimmid = dimslow = 1;

                            dimfast = dims[kdims-1];

                            if (kdims > 1) dimmid = dims[kdims-2];

                            if (kdims > 2) dimslow = total_dim/(dimfast*dimmid);

                            cbf_reportnez(cbf_set_integerarray_wdims_fs(handle,
                                                                        CBF_NIBBLE_OFFSET,target_row,*value,
                                                                        type_size,sign,total_dim,"little_endian",
                                                                        dimfast,dimmid,dimslow,0),errorcode);

                        }


                    }


                } else if (type_class==H5T_FLOAT){

                    /* Read of a single float or double or a float or
                     double array of up to 3 dimensions */

                    char * ivalue;

                    double dxdata;

                    float xdata;

                    if (total_dim ==1) {

                        cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                1,type_size*2+6),errorcode);

                        if (H5Tequal(native_type,H5T_NATIVE_FLOAT)) {

                            xdata = **((float **)value);

                            snprintf(ivalue,type_size*2+5,"%.7g",(double) xdata);

                        } else {

                            dxdata = **((double **)value);

                            snprintf(ivalue,type_size*2+5,"%.15g",dxdata);

                        }

                        cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                        cbf_reportnez(cbf_free((void**)value,NULL),errorcode);

                        *value = (unsigned char *)ivalue;

                    } else {



                        /* process arrays of up to 100 as
                         bracketed strings
                         */

                        if (total_dim < 101) {

                            size_t indices[H5S_MAX_RANK];

                            size_t master_index, ival_index;

                            int idim, level;

                            char buffer[40];

                            cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                    1,total_dim*((type_size*2)+5+kdims*2)+1),errorcode);

                            for (idim = 0; idim < kdims; idim ++) {

                                indices[idim] = 0;

                                ivalue[idim] = '[';

                            }

                            level = kdims-1;

                            ival_index = kdims;

                            master_index = 0;

                            while (master_index < total_dim) {

                                for (indices[level]=0; indices[level] < dims[level];) {

                                    if (H5Tequal(native_type,H5T_NATIVE_FLOAT)) {

                                        xdata = ((*(float **)value)[master_index]);

                                        snprintf(buffer,type_size*2+5,"%.7g",(double) xdata);

                                    } else {

                                        dxdata = ((*(double **)value)[master_index]);

                                        snprintf(buffer,type_size*2+5,"%.15g",dxdata);

                                    }

                                    strcat(ivalue+ival_index,buffer);

                                    ival_index+=strlen(buffer);

                                    ivalue[ival_index++]= (indices[level] < dims[level]-1)?',':']';

                                    master_index++;

                                    indices[level]++;

                                    if (indices[level] == dims[level]) {

                                        /* We are at the end of a fast-dimension row
                                         and therefore need to update higher level indices
                                         if any.  */

                                        indices[level] = 0;

                                        level --;

                                        while (level >= 0) {

                                            indices[level]++;

                                            if (indices[level] < dims[level]) {

                                                ivalue[ival_index++] = ',';

                                                ivalue[ival_index++] = '[';

                                                level++;

                                                break;

                                            } else {

                                                ivalue[ival_index++] = ']';

                                                indices[level] = 0;

                                                level --;

                                            }

                                        }

                                        if (level < 0) break;

                                        while (level > kdims-1) {

                                            ivalue[ival_index++] = '[';

                                            level++;

                                        }

                                    }

                                }

                            }

                            ivalue[ival_index++] = '\0';

                            cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                            cbf_reportnez(cbf_set_typeofvalue(handle,"bkts"),errorcode);

                            cbf_reportnez(cbf_free((void**)value,NULL),errorcode);

                            *value = (unsigned char *)ivalue;

                        } else {

                            size_t dimfast, dimmid, dimslow;

                            dimmid = dimslow = 1;

                            dimfast = dims[kdims-1];

                            if (kdims > 1) dimmid = dims[kdims-2];

                            if (kdims > 2) dimslow = total_dim/(dimfast*dimmid);

                            cbf_reportnez(cbf_set_realarray_wdims_fs(handle,
                                                                     CBF_NIBBLE_OFFSET,target_row,*value,
                                                                     type_size,total_dim,"little_endian",
                                                                     dimfast,dimmid,dimslow,0),errorcode);

                        }


                    }


                } else if (type_class != H5T_OPAQUE) {

                    unsigned char * hexvalue;

                    unsigned char hexdigs[16] = {'0','1','2','3','4','5','6','7','8','9',
                        'a','b','c','d','e','f'};

                    size_t ii;

                    cbf_reportnez(cbf_alloc(((void **) &hexvalue),NULL,
                                            1,2*total_size+1),errorcode);

                    hexvalue[2*total_size+1] = '\0';

                    for (ii=0; ii< total_size; ii++) {

                        hexvalue[(total_size-ii)*2-2] =
                        hexdigs[((int)(*((unsigned char **)value))[ii])&0xF];

                        hexvalue[(total_size-ii)*2-1] =
                        hexdigs[((int)((*((unsigned char **)value))[ii])>>4)&0xF];

                    }

                    cbf_reportnez(cbf_set_value(handle,(const char *)(hexvalue)),errorcode);

                    cbf_reportnez(cbf_free((void**)value,NULL),errorcode);

                    *value = hexvalue;

                }

            } else {

                /* process a dataset */

                hid_t memspace;

                memspace=H5Screate_simple(kdims,dims,NULL);

                cbf_reportnez(cbf_alloc(((void **) &data),NULL,
                                        1,total_size+1),errorcode);

                cbf_h5failneg(H5Dread(obj_id,native_type,
                                      H5S_ALL,memspace,H5P_DEFAULT,data),
                              CBF_ARGUMENT);

                data[total_size]='\0';

                if (type_class==H5T_STRING) {

                    cbf_reportnez(cbf_set_value(handle,(const char *)data),errorcode)

                } else if (type_class==H5T_INTEGER){

                    /* Read of a single integer or an integer array of
                     up to 3 dimensions */

                    char * ivalue;

                    long xdata = 0;

                    unsigned long uxdata = 0;

                    int sign;

                    sign = (type_sign==H5T_SGN_2)?1:0;

                    if (total_dim ==1) {

                        cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                1,type_size*3+1),errorcode);

                        if (H5Tequal(native_type, H5T_NATIVE_CHAR)&&sign) xdata = *((signed char *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_CHAR)&&!sign) uxdata = *((unsigned char *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_SCHAR)) xdata = *((signed char *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_UCHAR)) uxdata = *((unsigned char *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_SHORT)) xdata = *((unsigned short *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_USHORT)) uxdata = *((unsigned short *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_INT)) xdata = *((int *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_UINT)) uxdata = *((unsigned int *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_LONG)) xdata = *((long *)data);
                        if (H5Tequal(native_type, H5T_NATIVE_ULONG)) uxdata = *((unsigned long *)data);

                        if (sign) {

                            sprintf(ivalue,"%ld",xdata);

                        } else {

                            sprintf(ivalue,"%lu",uxdata);

                        }

                        cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                        cbf_reportnez(cbf_free((void**)&data,NULL),errorcode);

                        data = (unsigned char *)ivalue;

                    } else {



                        /* process arrays of up to 100 as
                         bracketed strings
                         */

                        if (total_dim < 101) {

                            size_t indices[H5S_MAX_RANK];

                            size_t master_index, ival_index;

                            int idim, level;

                            char buffer[40];

                            cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                    1,total_dim*((type_size*3)+kdims*2)+1),errorcode);

                            for (idim = 0; idim < kdims; idim ++) {

                                indices[idim] = 0;

                                ivalue[idim] = '[';

                            }

                            level = kdims-1;

                            ival_index = kdims;

                            master_index = 0;

                            while (master_index < total_dim) {

                                for (indices[level]=0; indices[level] < dims[level];) {

                                    if (H5Tequal(native_type, H5T_NATIVE_CHAR)
                                        &&sign) xdata = (((signed char *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_CHAR)
                                        &&!sign) uxdata = (((unsigned char *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_SCHAR)) xdata = (((signed char *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_UCHAR)) uxdata = (((unsigned char *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_SHORT)) xdata = (((unsigned short *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_USHORT)) uxdata = (((unsigned short *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_INT)) xdata = (((int *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_UINT)) uxdata = (((unsigned int *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_LONG)) xdata = (((long *)data)[master_index]);
                                    if (H5Tequal(native_type, H5T_NATIVE_ULONG)) uxdata = (((unsigned long *)data)[master_index]);


                                    if (sign) {

                                        sprintf(buffer,"%ld",xdata);

                                    } else {

                                        sprintf(buffer,"%lu",uxdata);

                                    }

                                    strcat(ivalue+ival_index,buffer);

                                    ival_index+=strlen(buffer);

                                    ivalue[ival_index++]= (indices[level] < dims[level]-1)?',':']';

                                    master_index++;

                                    indices[level]++;

                                    if (indices[level] == dims[level]) {

                                        /* We are at the end of a fast-dimension row
                                         and therefore need to update higher level indices
                                         if any.  */

                                        indices[level] = 0;

                                        level --;

                                        while (level >= 0) {

                                            indices[level]++;

                                            if (indices[level] < dims[level]) {

                                                ivalue[ival_index++] = ',';

                                                ivalue[ival_index++] = '[';

                                                level++;

                                                break;

                                            } else {

                                                ivalue[ival_index++] = ']';

                                                indices[level] = 0;

                                                level --;

                                            }

                                        }

                                        if (level < 0) break;

                                        while (level > kdims-1) {

                                            ivalue[ival_index++] = '[';

                                            level++;

                                        }

                                    }

                                }

                            }

                            ivalue[ival_index++] = '\0';

                            cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                            cbf_reportnez(cbf_set_typeofvalue(handle,"bkts"),errorcode);

                            cbf_reportnez(cbf_free((void**)&data,NULL),errorcode);

                            data = (unsigned char *)ivalue;

                        } else {

                            size_t dimfast, dimmid, dimslow;

                            dimmid = dimslow = 1;

                            dimfast = dims[kdims-1];

                            if (kdims > 1) dimmid = dims[kdims-2];

                            if (kdims > 2) dimslow = total_dim/(dimfast*dimmid);

                            cbf_reportnez(cbf_set_integerarray_wdims_fs(handle,
                                                                        CBF_NIBBLE_OFFSET,target_row,data,
                                                                        type_size,sign,total_dim,"little_endian",
                                                                        dimfast,dimmid,dimslow,0),errorcode);

                        }


                    }


                } else if (type_class==H5T_FLOAT){

                    /* Read of a single float or double or a float or
                     double array of up to 3 dimensions */

                    char * ivalue;

                    double dxdata;

                    float xdata;

                    if (total_dim ==1) {

                        cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                1,type_size*2+6),errorcode);

                        if (H5Tequal(native_type, H5T_NATIVE_FLOAT)) {

                            xdata = *((float *)data);

                            snprintf(ivalue,type_size*2+5,"%.7g",(double) xdata);

                        } else {

                            dxdata = *((double *)data);

                            snprintf(ivalue,type_size*2+5,"%.15g",dxdata);

                        }

                        cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                        cbf_reportnez(cbf_free((void**)&data,NULL),errorcode);

                        data = (unsigned char *)ivalue;

                    } else {



                        /* process arrays of up to 100 as
                         bracketed strings
                         */

                        if (total_dim < 101) {

                            size_t indices[H5S_MAX_RANK];

                            size_t master_index, ival_index;

                            int idim, level;

                            char buffer[40];

                            cbf_reportnez(cbf_alloc(((void **) &ivalue),NULL,
                                                    1,total_dim*((type_size*2)+5+kdims*2)+1),errorcode);

                            for (idim = 0; idim < kdims; idim ++) {

                                indices[idim] = 0;

                                ivalue[idim] = '[';

                            }

                            level = kdims-1;

                            ival_index = kdims;

                            master_index = 0;

                            while (master_index < total_dim) {

                                for (indices[level]=0; indices[level] < dims[level];) {

                                    if (H5Tequal(native_type, H5T_NATIVE_FLOAT)) {

                                        xdata = (((float *)data)[master_index]);

                                        snprintf(buffer,type_size*2+5,"%.7g",(double) xdata);

                                    } else {

                                        dxdata = (((double *)data)[master_index]);

                                        snprintf(buffer,type_size*2+5,"%.15g",dxdata);

                                    }

                                    strcat(ivalue+ival_index,buffer);

                                    ival_index+=strlen(buffer);

                                    ivalue[ival_index++]= (indices[level] < dims[level]-1)?',':']';

                                    master_index++;

                                    indices[level]++;

                                    if (indices[level] == dims[level]) {

                                        /* We are at the end of a fast-dimension row
                                         and therefore need to update higher level indices
                                         if any.  */

                                        indices[level] = 0;

                                        level --;

                                        while (level >= 0) {

                                            indices[level]++;

                                            if (indices[level] < dims[level]) {

                                                ivalue[ival_index++] = ',';

                                                ivalue[ival_index++] = '[';

                                                level++;

                                                break;

                                            } else {

                                                ivalue[ival_index++] = ']';

                                                indices[level] = 0;

                                                level --;

                                            }

                                        }

                                        if (level < 0) break;

                                        while (level > kdims-1) {

                                            ivalue[ival_index++] = '[';

                                            level++;

                                        }

                                    }

                                }

                            }

                            ivalue[ival_index++] = '\0';

                            cbf_reportnez(cbf_set_value(handle,(const char *)(ivalue)),errorcode);

                            cbf_reportnez(cbf_set_typeofvalue(handle,"bkts"),errorcode);

                            cbf_reportnez(cbf_free((void**)&data,NULL),errorcode);

                            data = (unsigned char *)ivalue;

                        } else {

                            size_t dimfast, dimmid, dimslow;

                            dimmid = dimslow = 1;

                            dimfast = dims[kdims-1];

                            if (kdims > 1) dimmid = dims[kdims-2];

                            if (kdims > 2) dimslow = total_dim/(dimfast*dimmid);

                            cbf_reportnez(cbf_set_realarray_wdims_fs(handle,
                                                                     CBF_NIBBLE_OFFSET,target_row,data,
                                                                     type_size,total_dim,"little_endian",
                                                                     dimfast,dimmid,dimslow,0),errorcode);

                        }


                    }


                } else if (type_class!= H5T_OPAQUE){

                    char * hexvalue;

                    char hexdigs[16] = {'0','1','2','3','4','5','6','7','8','9',
                        'a','b','c','d','e','f'};

                    size_t ii;

                    cbf_reportnez(cbf_alloc(((void **) &hexvalue),NULL,
                                            1,2*total_size+1),errorcode);

                    hexvalue[2*total_size+1] = '\0';

                    for (ii=0; ii< total_size; ii++) {

                        hexvalue[(total_size-ii)*2-2] =
                        hexdigs[((int)(((unsigned char *)data))[ii])&0xF];

                        hexvalue[(total_size-ii)*2-1] =
                        hexdigs[((int)((((unsigned char *)data))[ii])>>4)&0xF];

                    }

                    cbf_reportnez(cbf_set_value(handle,(const char *)(hexvalue)),errorcode);

                    cbf_reportnez(cbf_free((void**)&data,NULL),errorcode);

                    data = (unsigned char *)hexvalue;

                }


                if (value) {

                    *value=data;

                } else {

                    cbf_reportnez(cbf_free((void **)&data,NULL),errorcode);
                }

            }

        }
        switch(type_order) {
            case H5T_ORDER_LE:
                byte_order = "H5T_ORDER_LE";
                break;
            case H5T_ORDER_BE:
                byte_order = "H5T_ORDER_BE";
                break;
            case H5T_ORDER_VAX:
                byte_order = "H5T_ORDER_VAX";
                break;
            case H5T_ORDER_MIXED:
                byte_order = "H5T_ORDER_MIXED";
                break;
            case H5T_ORDER_NONE:
                byte_order = "H5T_ORDER_LE";
                break;
            case -1:
                byte_order = ".";
                break;
            default: byte_order="UNKNOWN";
                break;
        }

        cbf_reportnez(cbf_require_column(handle,"h5_byte_order"),errorcode);

        cbf_reportnez(cbf_set_value(handle,byte_order),errorcode);

        if (type_size < 10) {

            sprintf(buffer,"%ld",(unsigned long)type_size);

        } else {

            sprintf(buffer,"0x%lx",(unsigned long)type_size);

        }

        cbf_reportnez(cbf_require_column(handle,"size"),errorcode);

        cbf_reportnez(cbf_set_value(handle,buffer),errorcode);

        if (base_type >=0) H5Tclose(base_type);

        if (native_type>=0) H5Tclose(native_type);

        H5garbage_collect();

        return CBF_SUCCESS;
    }

    /* Callback routine for objects in a group */


    herr_t cbf_object_visit(hid_t loc_id, const char *name,
                            const H5L_info_t *info,
                            void *op_data){

        int cbfrow = -1;

        int errorcode;

        cbf_handle handle;

        haddr_t parent_addr;

        hid_t parent_id;

        unsigned int row;

        const char* parent_name;

        const char* grand_parent_name;

        int innexus;

        int incbf, incbfdb, incbfcat, incbfcol;

        hid_t group_id, dataset_id;

        herr_t retval;

        hsize_t i;

        char buffer[25];

        char digest[25];

        char *value;

        char cbftype[5];

        cbf_bookmark bookmark;

        cbf_bookmark saved_bookmark;

        H5O_info_t  objinfo;

        hid_t attrib_id,attrib_ds,attrib_type;

        hid_t dataset_ds, dataset_type;

        H5T_class_t dataset_type_class;

        ssize_t attrib_name_size;

        int attrib_num;

        unsigned int compression;

        int binary_id, bits, sign, type, checked_digest, realarray = 0;

        const char *byteorder;

        size_t binsize;

        size_t dimover, dimfast, dimmid, dimslow;

        size_t padding;

        errorcode = 0;

        handle = ((cbf_h5Ovisithandle)op_data)->handle;

        if (!handle) return -1;

        /* skip the root group itself */

        if (name[0]== '.') return 0;

        cbf_h5failneg(H5Oget_info_by_name(loc_id,
                                          name, &objinfo, H5P_DEFAULT),CBF_FORMAT);
        parent_id = ((cbf_h5Ovisithandle)op_data)->parent_id;

        parent_addr = ((cbf_h5Ovisithandle)op_data)->parent_addr;

        parent_name = ((cbf_h5Ovisithandle)op_data)->parent_name;

        grand_parent_name = ((cbf_h5Ovisithandle)op_data)->grand_parent_name;

        innexus = ((cbf_h5Ovisithandle)op_data)->innexus;

        incbf = ((cbf_h5Ovisithandle)op_data)->incbf;

        incbfdb = ((cbf_h5Ovisithandle)op_data)->incbfdb;

        incbfcat = ((cbf_h5Ovisithandle)op_data)->incbfcat;

        incbfcol = ((cbf_h5Ovisithandle)op_data)->incbfcol;

        memmove(&saved_bookmark,&(((cbf_h5Ovisithandle)op_data)->bookmark),sizeof(cbf_bookmark));

        switch (objinfo.type) {

            case H5O_TYPE_GROUP:

                /* Skip duplicates */

                for (i=0; i < ((cbf_h5Ovisithandle)op_data)->path_size; i++) {

                    if (objinfo.addr ==
                        ((cbf_h5Ovisithandle)op_data)->haddr_path[i])
                        return 0;

                }

                if (((cbf_h5Ovisithandle)op_data)->path_size >=
                    ((cbf_h5Ovisithandle)op_data)->capacity) {

                    size_t newcap;

                    newcap = 2*((cbf_h5Ovisithandle)op_data)->capacity;

                    cbf_reportnez(
                                  cbf_realloc(
                                              (void **)(&((cbf_h5Ovisithandle)op_data)->hid_path),
                                              NULL,sizeof(hid_t),newcap),errorcode);
                    cbf_reportnez(
                                  cbf_realloc(
                                              (void **)(&((cbf_h5Ovisithandle)op_data)->haddr_path),
                                              NULL,sizeof(haddr_t),newcap),errorcode);

                    ((cbf_h5Ovisithandle)op_data)->capacity=newcap;

                }

                (((cbf_h5Ovisithandle)op_data)->
                 haddr_path)[((cbf_h5Ovisithandle)op_data)->path_size] =
                objinfo.addr;

                group_id = H5Gopenx(loc_id,name);
                (((cbf_h5Ovisithandle)op_data)->
                 haddr_path)[((cbf_h5Ovisithandle)op_data)->path_size] =
                group_id;
                (((cbf_h5Ovisithandle)op_data)->path_size)++;

                /* We have a group
                 We need to add it to the H5_Groups category
                 in the H5 data block.

                 If it has attributes, we need to add them to
                 the H5Attributes category

                 If it has datasets, we will catch them when we
                 iterate again

                 */

                cbf_reportnez(cbf_rewind_datablock(handle),errorcode);

                if (cbf_find_datablock(handle,"H5")) {

                    cbf_reportnez(cbf_new_datablock(handle,"H5"),errorcode);

                }

                cbf_reportnez(cbf_require_category(handle,"H5_Groups"),errorcode);

                cbf_reportnez(cbf_new_row(handle),errorcode);

                cbf_reportnez(cbf_row_number(handle,&row),errorcode);

                cbf_reportnez(cbf_require_column(handle,"name"),errorcode);

                cbf_reportnez(cbf_set_value(handle,name),errorcode);

                cbf_reportnez(cbf_require_column(handle,"parent_name"),errorcode);

                cbf_reportnez(cbf_set_value(handle,parent_name),errorcode);

                cbf_reportnez(cbf_require_column(handle,"parent_id"),errorcode);

                if (!parent_addr) {

                    cbf_reportnez(cbf_set_value(handle,"."),errorcode);

                    cbf_reportnez(cbf_set_typeofvalue(handle,"null"),errorcode);

                } else {

                    sprintf(buffer,"0x%lx",(unsigned long)parent_addr);

                    cbf_reportnez(cbf_set_value(handle,buffer),errorcode);

                }

                cbf_reportnez(cbf_require_column(handle,"id"),errorcode);

                sprintf(buffer,"0x%lx",(unsigned long)objinfo.addr);

                cbf_reportnez(cbf_set_value(handle,buffer),errorcode);

                attrib_num = objinfo.num_attrs;

                cbf_reportnez(cbf_require_column(handle,"no_attributes"),errorcode);

                cbf_reportnez(cbf_set_integervalue(handle,attrib_num),errorcode);

                for (i=0; i < attrib_num; i++) {

                    char * attrib_name;
                    attrib_id=H5Aopen_by_idx(group_id,".",
                                             H5_INDEX_NAME,
                                             H5_ITER_INC,
                                             i,H5P_DEFAULT,H5P_DEFAULT);
                    attrib_ds = H5Aget_space(attrib_id);
                    attrib_type = H5Aget_type(attrib_id);
                    attrib_name_size = H5Aget_name(attrib_id,0,NULL);
                    cbf_reportnez(cbf_alloc(((void **) &attrib_name),NULL,
                                            1,attrib_name_size+1),errorcode);

                    cbf_h5failneg(H5Aget_name(attrib_id,
                                              attrib_name_size+1,attrib_name),
                                  CBF_ARGUMENT);
                    cbf_h5ds_store(handle,objinfo.addr,
                                   name,-1,
                                   "H5_Group_attribute",
                                   attrib_id,
                                   attrib_ds,
                                   attrib_type,
                                   attrib_name,1, (void **)&value);
                    if (!cbf_cistrcmp(attrib_name,"NX_class")&& value) {

                        cbf_reportnez(cbf_rewind_datablock(handle),errorcode);

                        if (cbf_find_datablock(handle,"H5")) {

                            cbf_reportnez(cbf_new_datablock(handle,"H5"),errorcode);

                        }


                        cbf_reportnez(cbf_require_category(handle,"H5_Groups"),errorcode);

                        cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

                        cbf_reportnez(cbf_select_row(handle,row),errorcode);

                        cbf_reportnez(cbf_require_column(handle,"NX_class"),errorcode);

                        cbf_reportnez(cbf_set_value(handle,value),errorcode);

                        if (!cbf_cistrcmp(value,"NXentry")) {

                            ((cbf_h5Ovisithandle)op_data)->innexus = 1;

                        }

                        if (!cbf_cistrcmp(value,"CBF_cbf")||!cbf_cistrcmp(value,"NXcbf")) {

                            ((cbf_h5Ovisithandle)op_data)->incbf = 1;

                        }

                        if (!cbf_cistrcmp(value,"CBF_cbfdb") || !cbf_cistrcmp(value,"NXcbfdb")) {

                            ((cbf_h5Ovisithandle)op_data)->incbfdb = 1;

                            cbf_get_bookmark(handle,&bookmark);

                            if (cbf_find_datablock(handle,name)) {

                                cbf_reportnez(cbf_new_datablock(handle,name),errorcode);

                            }

                            cbf_get_bookmark(handle,
                                             &(((cbf_h5Ovisithandle)op_data)->bookmark));

                            cbf_goto_bookmark(handle,bookmark);

                        }

                        if ((!cbf_cistrcmp(value,"CBF_cbfcat")||!cbf_cistrcmp(value,"NXcbfcat"))&& saved_bookmark.datablock) {

                            ((cbf_h5Ovisithandle)op_data)->incbfcat = 1;

                            cbf_get_bookmark(handle,&bookmark);

                            cbf_goto_bookmark(handle,saved_bookmark);

                            if (cbf_find_category(handle,name)) {

                                cbf_reportnez(cbf_new_category(handle,name),errorcode);

                            }

                            cbf_get_bookmark(handle,
                                             &(((cbf_h5Ovisithandle)op_data)->bookmark));

                            cbf_goto_bookmark(handle,bookmark);


                        }

                        if ((!cbf_cistrcmp(value,"CBF_cbfcol")
                             ||!cbf_cistrcmp(value,"NXcbfcol"))
                            && saved_bookmark.category) {

                            ((cbf_h5Ovisithandle)op_data)->incbfcol = 1;

                            cbf_get_bookmark(handle,&bookmark);

                            cbf_goto_bookmark(handle,saved_bookmark);

                            if (cbf_find_column(handle,name)) {

                                cbf_reportnez(cbf_new_column(handle,name),errorcode);

                            }

                            cbf_get_bookmark(handle,
                                             &(((cbf_h5Ovisithandle)op_data)->bookmark));

                            cbf_goto_bookmark(handle,bookmark);

                        }

                    }


                    cbf_reportnez(cbf_free((void **)&attrib_name,NULL),errorcode);
                    if (value) {
                        cbf_reportnez(cbf_free((void **)&value, NULL),errorcode);
                    }
                    H5Tclose(attrib_type);
                    H5Sclose(attrib_ds);
                    H5Aclose(attrib_id);
                }

                ((cbf_h5Ovisithandle)op_data)->parent_addr = objinfo.addr;

                ((cbf_h5Ovisithandle)op_data)->parent_id = group_id;

                cbf_reportnez(cbf_alloc((void **) &(((cbf_h5Ovisithandle)op_data)->parent_name),NULL,
                                        1,strlen(name)+1),errorcode);

                ((cbf_h5Ovisithandle)op_data)->grand_parent_name = parent_name;

                if (!name) return -1;

                strcpy((char *)((cbf_h5Ovisithandle)op_data)->parent_name,name);

                retval = H5Literate_by_name(loc_id, name,H5_INDEX_NAME,
                                            H5_ITER_INC,
                                            NULL,
                                            cbf_object_visit,op_data,H5P_DEFAULT);

                H5Gclose(group_id);

                cbf_reportnez(cbf_free((void **)(&((cbf_h5Ovisithandle)op_data)->parent_name),NULL),errorcode);

                (((cbf_h5Ovisithandle)op_data)->path_size)--;

                ((cbf_h5Ovisithandle)op_data)->parent_id = parent_id;

                ((cbf_h5Ovisithandle)op_data)->parent_addr = parent_addr;

                ((cbf_h5Ovisithandle)op_data)->parent_name = parent_name;

                ((cbf_h5Ovisithandle)op_data)->grand_parent_name = grand_parent_name;

                ((cbf_h5Ovisithandle)op_data)->innexus = innexus;

                ((cbf_h5Ovisithandle)op_data)->incbf = incbf;

                ((cbf_h5Ovisithandle)op_data)->incbfdb = incbfdb;

                ((cbf_h5Ovisithandle)op_data)->incbfcat = incbfcat;

                ((cbf_h5Ovisithandle)op_data)->incbfcol = incbfcol;

                return retval;
                break;

            case H5O_TYPE_DATASET:

                dataset_id = H5Dopen2(loc_id,name,H5P_DEFAULT);

                /* We have a dataset
                 We need to add it to the H5_Datasets category
                 in the current data block.

                 If it has attributes, we need to add them to
                 the H5_Attributes category

                 */


                cbf_reportnez(cbf_rewind_datablock(handle),errorcode);

                if (cbf_find_datablock(handle,"H5")) {

                    cbf_reportnez(cbf_new_datablock(handle,"H5"),errorcode);

                }

                cbf_reportnez(cbf_require_category(handle,"H5_Datasets"),errorcode);

                cbf_reportnez(cbf_new_row(handle),errorcode);

                cbf_reportnez(cbf_row_number(handle,&row),errorcode);

                cbf_reportnez(cbf_require_column(handle,"name"),errorcode);

                cbf_reportnez(cbf_set_value(handle,name),errorcode);

                cbf_reportnez(cbf_require_column(handle,"parent_name"),errorcode);

                cbf_reportnez(cbf_set_value(handle,parent_name),errorcode);

                cbf_reportnez(cbf_require_column(handle,"parent_id"),errorcode);

                if (!parent_addr) {

                    cbf_reportnez(cbf_set_value(handle,"."),errorcode);

                    cbf_reportnez(cbf_set_typeofvalue(handle,"null"),errorcode);

                } else {

                    sprintf(buffer,"0x%lx",(unsigned long)parent_addr);

                    cbf_reportnez(cbf_set_value(handle,buffer),errorcode);

                }

                cbf_reportnez(cbf_require_column(handle,"id"),errorcode);

                sprintf(buffer,"0x%lx",(unsigned long)objinfo.addr);

                cbf_reportnez(cbf_set_value(handle,buffer),errorcode);

                attrib_num = objinfo.num_attrs;

                cbf_reportnez(cbf_require_column(handle,"no_attributes"),errorcode);

                cbf_reportnez(cbf_set_integervalue(handle,attrib_num),errorcode);

                dimover = 0;

                binsize = 0;

                compression = 0;

                binary_id = 0;

                bits = 0;

                sign = 0;

                type = 0;

                byteorder = " ";

                dimfast=dimslow=dimmid = 0;

                padding = 0;

                cbftype[0] = '\0';

                for (i=0; i < attrib_num; i++) {

                    char * attrib_name;
                    attrib_id=H5Aopen_by_idx(dataset_id,".",
                                             H5_INDEX_NAME,
                                             H5_ITER_INC,
                                             i,H5P_DEFAULT,H5P_DEFAULT);
                    attrib_ds = H5Aget_space(attrib_id);
                    attrib_type = H5Aget_type(attrib_id);
                    attrib_name_size = H5Aget_name(attrib_id,0,NULL);
                    cbf_reportnez(cbf_alloc(((void **) &attrib_name),NULL,
                                            1,attrib_name_size+1),errorcode);

                    cbf_h5failneg(H5Aget_name(attrib_id,
                                              attrib_name_size+1,attrib_name),
                                  CBF_ARGUMENT);
                    cbf_h5ds_store(handle,objinfo.addr,
                                   name,-1,
                                   "H5_Dataset_attribute",
                                   attrib_id,
                                   attrib_ds,
                                   attrib_type,
                                   attrib_name,1,(void **)&value);
                    if (*value) {


                        cbf_reportnez(cbf_rewind_datablock(handle),errorcode);

                        if (cbf_find_datablock(handle,"H5")) {

                            cbf_reportnez(cbf_new_datablock(handle,"H5"),errorcode);

                        }

                        cbf_reportnez(cbf_require_category(handle,"H5_Datasets"),errorcode);

                        cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

                        cbf_reportnez(cbf_select_row(handle,row),errorcode);

                        cbf_reportnez(cbf_require_column(handle,attrib_name),errorcode);

                        cbf_reportnez(cbf_set_value(handle,value),errorcode);

                        if (!cbf_cistrcmp(attrib_name,"compression")) {
                            compression=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"binid")) {
                            binary_id=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"bits")) {
                            bits=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"sign")) {
                            sign = (int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"bintype")) {
                            type=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"checked_digest")) {
                            checked_digest=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"real")) {
                            realarray = (int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"byteorder")) {
                            byteorder=
                            (value[0]=='l'||value[0]=='L')?
                            "little_endian":"big_endian";
                        } else if (!cbf_cistrcmp(attrib_name,"size")) {
                            binsize = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"digest")
                                   ||!cbf_cistrcmp(attrib_name,"MD5_digest")) {
                            strncpy(digest,value,24);
                            digest[24] = 0;
                        } else if (!cbf_cistrcmp(attrib_name,"dimover")) {
                            dimover = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimfast")) {
                            dimfast = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimmid")) {
                            dimmid = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimslow")) {
                            dimslow = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"padding")) {
                            padding = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"cbftype")) {
                            strncpy(cbftype,value,4);
                            cbftype[4] = '\0';
                        }
                    }

                    cbf_reportnez(cbf_free((void **)&attrib_name,NULL),errorcode);
                    if (value) cbf_reportnez(cbf_free((void **)&value, NULL),errorcode);
                    H5Tclose(attrib_type);
                    H5Sclose(attrib_ds);
                    H5Aclose(attrib_id);
                }

                dataset_ds         = H5Dget_space(dataset_id);
                dataset_type       = H5Dget_type(dataset_id);
                dataset_type_class = H5Tget_class(dataset_type);

                cbf_h5ds_store(handle,objinfo.addr,
                               parent_name,row,
                               "H5_Datasets",
                               dataset_id,
                               dataset_ds,
                               dataset_type,
                               name,0,(void **)&value);

                if (incbfcol&&value) {

                    cbfrow = (int)strtol(name,NULL,0);

                    cbf_get_bookmark(handle,&bookmark);

                    cbf_goto_bookmark(handle,saved_bookmark);

                }

                if (incbfcol&&binsize&&value) {

                    size_t elsize, nelem;

                    cbf_node * column;

                    cbf_file *tempfile;

                    long start;

                    unsigned int localrow, ii;

                    elsize = (bits+CHAR_BIT-1)/CHAR_BIT;

                    nelem = (binsize+elsize-1)/elsize;

                    if (dimover <=0) dimover = nelem;

                    localrow = row;

                    if (nelem > 0 && elsize > 0) {

                        if (incbfcol) {

                            unsigned int rows;

                            cbf_reportnez(cbf_count_rows(handle,&rows),errorcode);

                            if (cbfrow >= rows) {

                                for (ii=rows; ii <= cbfrow; ii++) {

                                    cbf_reportnez(cbf_new_row(handle),errorcode);
                                }

                            }

                            cbf_select_row(handle,cbfrow);

                            localrow = cbfrow;

                        } else {


                            cbf_reportnez(cbf_rewind_datablock(handle),errorcode);

                            if (cbf_find_datablock(handle,"H5")) {

                                cbf_reportnez(cbf_new_datablock(handle,"H5"),errorcode);

                            }


                            cbf_reportnez(cbf_require_category(handle,"H5_Datasets"),errorcode);

                            cbf_reportnez(cbf_find_column(handle,"id"),errorcode);

                            cbf_reportnez(cbf_select_row(handle,localrow),errorcode);

                            cbf_reportnez(cbf_require_column(handle,"value"),errorcode);

                        }

                        column = handle->node;

                        if (dataset_type_class == H5T_OPAQUE) {

                            /* If we have stored as an opqaue dataset, keep it that way */


                            /* Remove the old value */

                            cbf_reportnez (cbf_set_columnrow (column, localrow, NULL, 1),errorcode)


                            /* Get the temporary file */

                            cbf_reportnez (cbf_open_temporary (column->context, &tempfile),errorcode)


                            /* Move to the end of the temporary file */

                            if (cbf_set_fileposition (tempfile, 0, SEEK_END))

                                return CBF_FILESEEK | cbf_delete_fileconnection (&tempfile);


                            /* Get the starting location */

                            if (cbf_get_fileposition (tempfile, &start))

                                return CBF_FILETELL | cbf_delete_fileconnection (&tempfile);


                            /* Discard any bits in the buffers */

                            cbf_reportnez (cbf_reset_bits (tempfile),errorcode)

                            /* Add the binary data to the temporary file */

                            if (!cbf_set_output_buffersize(tempfile,binsize))  {

                                memmove((void *)(tempfile->characters+tempfile->characters_used),
                                        (void *)value,binsize);

                                tempfile->characters_used+=binsize;

                            }

                            cbf_onfailnez(cbf_set_bintext(column,localrow,CBF_TOKEN_TMP_BIN,
                                                          binary_id,tempfile,start,binsize,
                                                          1,digest,bits,sign,realarray,byteorder,
                                                          dimover, dimfast, dimmid, dimslow,
                                                          padding,compression),
                                          cbf_delete_fileconnection (&tempfile));

                            cbf_onfailnez(cbf_flush_bits(tempfile),
                                          cbf_delete_fileconnection (&tempfile));
                        } else {

                            /* If this is not an opqaue object, then recompress
                             using the attributes */

                            cbf_reportnez(cbf_set_binary(handle->node,
                                                         handle->row,
                                                         compression,
                                                         binary_id,
                                                         (void *) value,
                                                         (bits+7)/8,
                                                         sign,
                                                         dimover,
                                                         realarray,
                                                         "little_endian",
                                                         dimover,
                                                         dimfast,
                                                         dimmid,
                                                         dimslow,
                                                         padding ), errorcode);

                        }

                    }

                } else {

                    if (incbfcol && value) {

                        unsigned int rows;

                        cbf_reportnez(cbf_count_rows(handle,&rows),errorcode);

                        if (cbfrow >= rows) {

                            cbf_reportnez(cbf_insert_row(handle,cbfrow),errorcode);

                        }

                        cbf_reportnez(cbf_select_row(handle,cbfrow),errorcode);

                        cbf_reportnez(cbf_set_value(handle,value),errorcode);

                        if (cbftype[0] && cbf_cistrcmp(cbftype,"(null)")
                            && strlen(cbftype) == 4) {

                            cbf_reportnez(cbf_set_typeofvalue(handle,cbftype),errorcode);

                        }

                    }

                }

                if (incbfcol&&value) {

                    cbf_reportnez(cbf_goto_bookmark(handle,bookmark),errorcode);

                }
                if (value) cbf_reportnez(cbf_free((void **)&value, NULL),errorcode);
                H5Dclose(dataset_id);
                H5Sclose(dataset_ds);
                H5Tclose(dataset_type);

                break;

            case H5O_TYPE_NAMED_DATATYPE:

                break;

            default:

                return CBF_FORMAT;



        }

        return 0;
    }
    /* Read an HDF5 file */

    int cbf_read_h5file(const cbf_handle handle,
                        const cbf_h5handle h5handle,
                        const int flags) {

        cbf_node *node;

        cbf_h5Ovisit_struct h5Ovisit;

        if (!handle || !h5handle || !h5handle->hfile ) return CBF_ARGUMENT;

        /* Move the flags into the h5handle */

        h5handle -> flags = flags;

        /* Delete the old datablocks */

        if( handle->commentfile) cbf_failnez (cbf_free_file (&(handle->commentfile)));

        cbf_failnez (cbf_find_parent (&node, handle->node, CBF_ROOT));

        cbf_failnez (cbf_set_children (node, 0))

        handle->node = node;

        cbf_failnez (cbf_reset_refcounts(handle->dictionary));

        /* register the CBF compressions if requested */

        if (h5handle->flags & CBF_H5_REGISTER_COMPRESSIONS) {

            if (!H5Zfilter_avail(CBF_H5Z_FILTER_CBF)) {

                cbf_h5failneg(H5Zregister(CBF_H5Z_CBF),CBF_ALLOC);

            }
        }

        h5Ovisit.handle = handle;

        h5Ovisit.h5handle = h5handle;

        h5Ovisit.parent_addr = 0;

        h5Ovisit.parent_id = h5handle->hfile;

        h5Ovisit.parent_name = "/";

        h5Ovisit.grand_parent_name = NULL;

        h5Ovisit.incbf = h5Ovisit.incbfdb = h5Ovisit.incbfcat = h5Ovisit.incbfcol = 0;

        h5Ovisit.innexus = 0;

        h5Ovisit.bookmark.datablock = NULL;

        h5Ovisit.bookmark.category = NULL;

        h5Ovisit.bookmark.column = NULL;

        h5Ovisit.bookmark.haverow = 0;


        cbf_failnez(cbf_alloc ((void **) (&(h5Ovisit.hid_path)), NULL,
                               sizeof(hid_t), 1));

        cbf_failnez(cbf_alloc ((void **) (&(h5Ovisit.haddr_path)), NULL,
                               sizeof(haddr_t), 1));

        h5Ovisit.capacity = 1;

        h5Ovisit.path_size = 0;

        cbf_failnez(cbf_new_datablock(handle,"H5"));

        /* visit the groups in the file, starting with the root group */

        cbf_h5failneg(H5Literate(h5handle->hfile,
                                 H5_INDEX_NAME,
                                 H5_ITER_INC,
                                 NULL,
                                 cbf_object_visit,(void *)&h5Ovisit),CBF_FORMAT);

        return CBF_SUCCESS;

    }
    
    /* get a fast bookmark from the current information in a cbf handle */

    int cbf_get_fast_bookmark(const cbf_handle handle,
                              cbf_fast_bookmark * bookmark) {

        if (!handle || !bookmark) return CBF_ARGUMENT;

        bookmark->node = handle->node;

        bookmark->row = handle->row;

        return CBF_SUCCESS;

    }

    /* go to a fast bookmark in a cbf handle */

    int cbf_goto_fast_bookmark(const cbf_handle handle,
                              const cbf_fast_bookmark bookmark) {

        if (!handle) return CBF_ARGUMENT;

        handle->node = bookmark.node;

        handle->row = bookmark.row;

        return CBF_SUCCESS;

    }

    /* get a bookmark from the current information in a cbf handle */

    int cbf_get_bookmark(const cbf_handle handle,
                         cbf_bookmark * bookmark) {

        if (cbf_datablock_name(handle,&(bookmark->datablock))) {

            bookmark->datablock = NULL;

        }

        if (cbf_category_name(handle,&(bookmark->category))) {

            bookmark->category = NULL;

        }

        if (cbf_column_name(handle,&(bookmark->column))) {

            bookmark->column = NULL;

        }

        bookmark->haverow = 1;

        if (cbf_row_number(handle,&(bookmark->row))) {

            bookmark->row = 0;

            bookmark->haverow = 0;

        }

        return CBF_SUCCESS;

    }

    /* go to a bookmark in the cbf handle */

    int cbf_goto_bookmark(const cbf_handle handle,
                          const cbf_bookmark bookmark) {

        unsigned int rows;

        if (bookmark.datablock) {

            cbf_failnez(cbf_rewind_datablock(handle));

            cbf_failnez(cbf_find_datablock(handle,bookmark.datablock));

            if (bookmark.category) {

                cbf_failnez(cbf_rewind_category(handle));

                cbf_failnez(cbf_find_category(handle,bookmark.category));

                if (bookmark.column) {

                    cbf_failnez(cbf_rewind_column(handle));

                    cbf_failnez(cbf_find_column(handle,bookmark.column));

                    if (bookmark.haverow) {

                        cbf_failnez(cbf_count_rows(handle,&rows));

                        if (bookmark.row < rows) {

                            cbf_failnez(cbf_select_row(handle,bookmark.row));

                        }

                    }

                }


            }

        }

        return CBF_SUCCESS;
	}

#ifdef __cplusplus

}

#endif
